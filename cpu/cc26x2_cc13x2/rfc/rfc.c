/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         cpu_cc26x2_cc13x2
 * @{
 *
 * @file
 * @brief           CC26x2/CC13x2 RF Core common functions
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 * @}
 */

#include "cpu.h"
#include "cc26x2_cc13x2_rfc.h"
#include "cc26xx_cc13xx_power.h"

#define ENABLE_DEBUG (0)
#include "debug.h"

static uint32_t _rfc_execute_sync(uint32_t cmd);

/**
 * @brief   Command and Packet Engine (CPE) patch function
 */
static void (* _cpe_patch_fn)(void);
/**
 * @brief   Radio Timer offset
 */
static rfc_ratmr_t _rat_offset;
/**
 * @brief   ISR handler callback
 */
static void (* _handler_cb)(void);
/**
 * @brief   Last issued radio operation
 */
static rfc_op_t *_last_command;

static inline rfc_op_t *_last_in_chain(rfc_op_t *op)
{
    rfc_op_t *curr_op = op;
    while (curr_op != NULL) {
        curr_op = curr_op->next_op;
    }

    return curr_op;
}

void cc26x2_cc13x2_rfc_init(void (* cpe_patch_fn)(void),
                            void (* handler_cb)(void))
{
    assert(handler_cb != NULL);

    _cpe_patch_fn = cpe_patch_fn;
    _rat_offset = 0;
    _last_command = NULL;
    _handler_cb = handler_cb;

    /* We don't use the modes on PRCM->RFCMODEHWOPT since that is not
     * documented, writing a 0 means to select the mode automatically. On cc13x0
     * it's needed to write one of the valid modes specified at
     * PRCM->RFCMODEHWOPT. On cc26x0 it's fine to write 0 */
    PRCM->RFCMODESEL = 0;
}

int cc26x2_cc13x2_rfc_power_on(void)
{
    unsigned key = irq_disable();

    /* Enable RF Core power domain */
    if (!power_is_domain_enabled(POWER_DOMAIN_RFC)) {
        power_enable_domain(POWER_DOMAIN_RFC);
    }

    /* Enable RF Core clock */
    power_clock_enable_rfc();

    /* At this point RF Core registers are available, disable and remove
     * previous interrupts (if any) */
    RFC_DBELL_NONBUF->RFCPEIFG = 0;
    RFC_DBELL_NONBUF->RFCPEIEN = 0;

    /* Select all interrupts for RF_CPE0_IRQN, and CPE_IRQ_INTERNAL_ERROR */
    RFC_DBELL_NONBUF->RFCPEISL = 0;
    RFC_DBELL_NONBUF->RFCPEISL |= CPE_IRQ_INTERNAL_ERROR;

    NVIC_ClearPendingIRQ(RF_CPE0_IRQN);
    NVIC_ClearPendingIRQ(RF_CPE1_IRQN);
    NVIC_EnableIRQ(RF_CPE0_IRQN);
    NVIC_EnableIRQ(RF_CPE1_IRQN);

    /* Enable internal error interrupt (handled on isr_rfc_cpe1) */
    RFC_DBELL_NONBUF->RFCPEIEN |= CPE_IRQ_INTERNAL_ERROR;

    /* Let CPE boot */
    RFC_PWR_NONBUF->PWMCLKEN = PWMCLKEN_CPERAM | PWMCLKEN_CPE | PWMCLKEN_RFC;

    /* Wait while RF Core boots up */
    while (!(RFC_DBELL->RFCPEIFG & CPE_IRQ_MODULES_UNLOCKED) &&
           !(RFC_DBELL->RFCPEIFG & CPE_IRQ_BOOT_DONE)) {}
    RFC_DBELL_NONBUF->RFCPEIFG = ~(CPE_IRQ_MODULES_UNLOCKED | CPE_IRQ_BOOT_DONE);

    /* Perform the switch to XOSC_HF */
    osc_hf_source_switch(OSC_XOSC_HF);

    /* Patch CPE */
    if (_cpe_patch_fn != NULL) {
        _cpe_patch_fn();
    }

    /* Turn on the clock line to the radio core, this is necessary to use the
     * CMD_SYNC_START_RAT and the CMD_SYNC_STOP_RAT commands. */
    AON_RTC->CTL |= AON_RTC_CTL_RTC_UPD_EN;

    irq_restore(key);

    return 0;
}

rfc_op_t *cc26x2_cc13x2_rfc_last_cmd(void)
{
    return _last_command;
}

uint32_t cc26x2_cc13x2_rfc_send_cmd(rfc_op_t *op)
{
    assert(op);

    unsigned key = irq_disable();

    /* Find the last operation in the chain (if any) */
    rfc_op_t *curr_op = _last_in_chain(_last_command);

    /* Wait while the last operation finishes */
    while (curr_op->status == RFC_PENDING ||curr_op->status == RFC_ACTIVE) {}

    _last_command = op;

    uint32_t cmdsta = _rfc_execute_sync((uint32_t)_last_command);

    irq_restore(key);

    return cmdsta;
}

void cc26x2_cc13x2_rfc_abort_cmd(void)
{
    if ((_rfc_execute_sync(RFC_CMDR_DIR_CMD(RFC_CMD_STOP)) & 0xFF) != RFC_CMDSTA_DONE) {
        DEBUG_PUTS("rfc_abort_cmd: couldn't execute CMD_STOP");
    }
}

/**
 * @brief   Send a command syncrhonously to the RF Core
 *
 * @param[in] cmd The command.
 */
static uint32_t _rfc_execute_sync(uint32_t cmd)
{
    unsigned key = irq_disable();

    /* Wait until the doorbell becomes available */
    while (RFC_DBELL->CMDR != 0) {}
    RFC_DBELL->RFACKIFG = 0;

    /* Submit the command to the CM0 through the doorbell */
    RFC_DBELL->CMDR = cmd;

    /* Wait until the CM0 starts to parse the command */
    while (!RFC_DBELL->RFACKIFG) {}
    RFC_DBELL->RFACKIFG = 0;

    /* Return the content of status register */
    uint32_t cmdsta = RFC_DBELL->CMDSTA;
    irq_restore(key);

    return cmdsta;
}

void isr_rfc_cpe0(void)
{
    _handler_cb();
    cortexm_isr_end();
}

void isr_rfc_cpe1(void)
{
    DEBUG_PUTS("isr_rfc_cpe1: internal error");
    RFC_DBELL_NONBUF->RFCPEIFG = ~CPE_IRQ_INTERNAL_ERROR;
    cortexm_isr_end();
}
