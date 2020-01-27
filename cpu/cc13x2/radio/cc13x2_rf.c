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

#define ENABLE_DEBUG (1)
#include "debug.h"

void cc13x2_rf_init(void)
{
    unsigned int interrupts_disabled = irq_disable();

    /* Check if the RF Core is off and initialize it if it's off */
    if (!prcm_rf_ready()) {
        cc13x2_rf_power_up();
    }

    if (!interrupts_disabled) {
        irq_enable();
    }
}

void cc13x2_rf_setup(void)
{
    cc13x2_rf_init();
}
