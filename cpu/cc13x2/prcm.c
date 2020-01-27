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
 * @brief           CC13x2 PRCM support code
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 * @}
 */

#include <stddef.h>

#include "cpu.h"

#include "cc13x2_prcm.h"

void prcm_set_rfc_powerdomain_on(void)
{
    PRCM->PDCTL0RFC = 1;
}

int_fast8_t prcm_get_rfc_powerdomain_status(void)
{
    return (PRCM->PDSTAT0 & PDSTAT0_RFC_ON) != 0 &&
           (PRCM->PDSTAT1 & PDSTAT1_RFC_ON) != 0;
}

void prcm_enable_rfc_domain(void)
{
    PRCM->RFCCLKG = RFCCLKG_CLK_EN;
}

void prcm_set_load(void)
{
    /* Write CLKLOADCTL so RFC clock enable takes effect */
    PRCM_NONBUF->CLKLOADCTL = CLKLOADCTL_LOAD;
}

int_fast8_t prcm_is_load_done(void)
{
    return (PRCM->CLKLOADCTL & CLKLOADCTL_LOADDONE) != 0;
}
