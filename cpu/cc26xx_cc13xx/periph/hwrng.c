/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_cc26xx_cc13xx
 * @ingroup     drivers_periph_hwrng
 * @{
 *
 * @file
 * @brief       CC26xx/CC13xx Low-level HWRNG driver implementation
 *
 * @author      Jean Pierre Dudey <jeandudey@hotmail.com>
 * @}
 */

#include <stdlib.h>
#include <stdio.h>

#include "assert.h"
#include "board.h"
#include "cpu.h"
#include "periph_conf.h"
#include "periph/hwrng.h"

#include "cc26xx_cc13xx_power.h"

#define ENABLE_DEBUG (0)
#include "debug.h"

void hwrng_init(void)
{
    if (!power_is_domain_enabled(POWER_DOMAIN_PERIPHERALS)) {
        power_enable_domain(POWER_DOMAIN_PERIPHERALS);
    }
}

void hwrng_read(void)
{
    TRNG->IRQFLAGCLR = (IRQFLAGCLR_SHUTDOWN_OVF | IRQ_FLAGCLR_RDY);
}

void isr_trng(void)
{
    cortexm_end_isr();
}
