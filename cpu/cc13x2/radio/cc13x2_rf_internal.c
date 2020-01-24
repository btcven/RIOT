/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         cpu_cc13x2
 * @{
 *
 * @file
 * @brief           CC13x2 radio driver
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#include "cpu.h"
#include "cc13x2_rf_internal.h"

#define ENABLE_DEBUG (1)
#include "debug.h"

#define RF_BOOT0 (0xE0000011) /**< RF Core boot parameters */

static rfc_radio_op_t *_last_radio_op;

void cc13x2_rf_power_up(void)
{
    unsigned int interrupts_disabled = irq_disable();

    DEBUG_PUTS("Initializing CC13x2 radio");

    NVIC_ClearPendingIRQ(RF_CPE0_IRQN);
    NVIC_ClearPendingIRQ(RF_CPE1_IRQN);
    NVIC_DisableIRQ(RF_CPE0_IRQN);
    NVIC_DisableIRQ(RF_CPE1_IRQN);

    /* Set RFC boot parameters */
    PRCM->RFCBITS = RF_BOOT0;

    /* Enable RTC_UPD clock */
    AON_RTC->CTL |= CTL_RTC_UPD_EN;

    /* Set RF Core power domain to "on" */
    PRCM->PDCTL0RFC = 1;

    /* Wait until power domain is updated */
    while ((PRCM->PDSTAT0 & PDSTAT0_RFC_ON) == 0
        || (PRCM->PDSTAT1 & PDSTAT1_RFC_ON) == 0) {}


    /* Enable RFC clock */
    PRCM->RFCCLKG = RFCCLKG_CLK_EN;

    /* Write CLKLOADCTL so RFC clock enable takes effect */
    PRCM_NONBUF->CLKLOADCTL = CLKLOADCTL_LOAD;
    while ((PRCM->CLKLOADCTL & CLKLOADCTL_LOADDONE) == 0) {}

    /* Disable CPE interrupts */
    RFC_DBELL_NONBUF->RFCPEIFG = 0;
    RFC_DBELL_NONBUF->RFCPEIEN = 0;
    NVIC_EnableIRQ(RF_CPE0_IRQN);
    NVIC_EnableIRQ(RF_CPE1_IRQN);

    if (!interrupts_disabled) {
        irq_enable();
    }

    /* Let CPE boot */
    RFC_PWR_NONBUF->PWMCLKEN = PWMCLKEN_CPERAM
                             | PWMCLKEN_CPE
                             | PWMCLKEN_RFC;

    /* Reset interrupt flags */
    RFC_DBELL->RFCPEIFG = 0;

    /* Ping the CPE to see if it's alive */
    uint32_t res = 0;
    if (cc13x2_rf_send_cmd(CMDR_DIR_CMD(CMD_PING), &res) != 0) {
        DEBUG_PUTS("Ping failed!");
        return;
    }

    DEBUG_PUTS("CPE booted");
}

int cc13x2_rf_send_cmd(uint32_t cmd, uint32_t *status)
{
    bool is_radio_op = false;
    /* If cmd is 4-byte aligned, then it's either a radio OP or an immediate
     * command. Clear the status field if it's a radio OP
     */
    if ((cmd & 0x03) == 0) {
        uint32_t cmd_type = ((rfc_command_t *)cmd)->command_no & COMMAND_TYPE_mask;
        if (cmd_type == COMMAND_TYPE_IEEE_FG_RADIO_OP
         || cmd_type == COMMAND_TYPE_RADIO_OP) {
            is_radio_op = true;
            ((rfc_radio_op_t *)cmd)->status = RADIO_OP_STATUS_IDLE;
        }
    }

    unsigned int interrupts_disabled = irq_disable();

    /* Check if the RF Core is on */
    if ((PRCM->PDSTAT1 & PDSTAT1_RFC_ON) == 0) {
        DEBUG_PUTS("RF is off!");
        if (!interrupts_disabled) {
            irq_enable();
        }
        return -1;
    }

    if (is_radio_op) {
        uint16_t command_no = ((rfc_radio_op_t *)cmd)->command_no;
        if ((command_no & COMMAND_PROTOCOL_mask) != COMMAND_PROTOCOL_COMMON
         && (command_no & COMMAND_TYPE_mask) == COMMAND_TYPE_RADIO_OP) {
            _last_radio_op = (rfc_radio_op_t *)cmd;
        }
    }

    /* Wait while CMDR becomes available */
    while (RFC_DBELL->CMDR != 0) {}

    /* Send command to the doorbell */
    RFC_DBELL->CMDR = cmd;

    /* Wait until command is done */
    int timeout_count = 0;
    do {
        *status = RFC_DBELL->CMDSTA;
        DEBUG("cc13x2_rf_send_cmd: CMDSTA = %08lx\n", *status);
        if (++timeout_count > 50000) {
            DEBUG("command 0x%08lx timed out\n", cmd);
            if(!interrupts_disabled) {
                irq_enable();
            }
            return -1;
        }
    } while((*status & CMDSTA_RESULT_mask) == CMDSTA_RESULT_PENDING);

    DEBUG("cc13x2_rf_send_cmd: enable interrupts\n");

    if (!interrupts_disabled) {
        irq_enable();
    }

    DEBUG("CMDSTA.RESULT = %02lx\n", *status & CMDSTA_RESULT_mask);

    /* The command is no longer pending. It is either completed successfully or
     * with error */
    if (((*status & CMDSTA_RESULT_mask) == CMDSTA_RESULT_DONE)) {
        return 0;
    }
    else {
        return -1;
    }
}
