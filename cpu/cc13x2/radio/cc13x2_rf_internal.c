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
 * @brief           CC13x2 radio
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 * @}
 */

#include "cpu.h"
#include "cc13x2_rf_internal.h"

#define RF_BOOT0          (0xE0000011) /**< RF Core boot parameters */

void cc13x2_rf_internal_init(void)
{
    /* Enable RTC_UPD */
    AON_RTC->CTL |= CTL_RTC_UPD_EN;

    /* Set RF Core boot parameters */
    PRCM->RFCBITS = RF_BOOT0;
}

void isr_rfc_cpe1(void)
{
}

void isr_rfc_cpe0(void)
{
}

void isr_rfc_hw(void)
{
}

void isr_rfc_cmd_ack(void)
{
}
