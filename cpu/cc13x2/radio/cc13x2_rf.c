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
 * @}
 */

#include "cc13x2_rf.h"
#include "cc13x2_rf_internal.h"
#include "rf_conf.h"

#define ENABLE_DEBUG (1)
#include "debug.h"

void cc13x2_rf_init(void)
{
    unsigned int interrupts_disabled = irq_disable();

    /* Check if the RF Core is off and initialize it if it's off */
    if ((PRCM->PDSTAT1 & PDSTAT1_RFC_ON) == 0) {
        cc13x2_rf_power_up();
    }

    /* Select the radio mode */
    PRCM->RFCMODESEL = CC13X2_RF_MODE;

    if (!interrupts_disabled) {
        irq_enable();
    }

    rf_cmd_prop_radio_div_setup.lodivider = CC13X2_RF_LO_DIVIDER;

    DEBUG("cc13x2_rf_init: sending setup command\n");

    /* Send the CMD_PROP_RADIO_DIV_SETUP command */
    uint32_t cmd_res;
    if (cc13x2_rf_send_cmd((uint32_t)&rf_cmd_prop_radio_div_setup, &cmd_res) != 0) {
        DEBUG("cc13x2_rf_init: CMDSTA = %08lx", cmd_res);
        return;
    }

    DEBUG("cc13x2_rf_init: CMDSTA = %08lx", cmd_res);
}

void cc13x2_rf_setup(void)
{
    cc13x2_rf_init();
}
