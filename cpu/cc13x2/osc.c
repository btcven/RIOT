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
 * @brief           CC13x2 OSC support code
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 * @}
 */

#include <stddef.h>

#include "cpu.h"

#include "cc13x2_osc.h"
#include "cc13x2_ddi.h"
#include "cc13x2_prcm.h"

uint32_t osc_get_clock_source(uint32_t srcclk)
{
    /* Check the argument */
    assert((srcclk & OSC_SRC_CLK_LF) || (srcclk & OSC_SRC_CLK_HF));

    if (srcclk == OSC_SRC_CLK_LF) {
        return ddi_read_bitfield_16(DDI0_OSC_BASE,
                                    offsetof(ddi0_osc_regs_t, STAT0),
                                    DDI_0_OSC_STAT0_SCLK_LF_SRC_M,
                                    DDI_0_OSC_STAT0_SCLK_LF_SRC_S);
    }

    return ddi_read_bitfield_16(DDI0_OSC_BASE,
                                offsetof(ddi0_osc_regs_t, STAT0),
                                DDI_0_OSC_STAT0_SCLK_HF_SRC_M,
                                DDI_0_OSC_STAT0_SCLK_HF_SRC_S);
}

void osc_set_clock_source(uint32_t srcclk, uint32_t osc)
{
    /* Check the arguments */
    assert((srcclk & OSC_SRC_CLK_LF) || (srcclk & OSC_SRC_CLK_HF));
    assert((osc == OSC_RCOSC_HF) ||
           (osc == OSC_RCOSC_LF) ||
           (osc == OSC_XOSC_HF) ||
           (osc == OSC_XOSC_LF));

    /* Request the high frequency source clock (using 24 MHz XTAL) */
    if (srcclk & OSC_SRC_CLK_HF) {
        /* Enable the HF XTAL as HF clock source */
        ddi_write_bitfield_16(DDI0_OSC_BASE,
                              offsetof(ddi0_osc_regs_t, CTL0),
                              DDI_0_OSC_CTL0_SCLK_HF_SRC_SEL,
                              DDI_0_OSC_CTL0_SCLK_HF_SRC_SEL_S,
                              osc);
    }
    /* Configure the low frequency source clock */
    else if (srcclk & OSC_SRC_CLK_LF) {
        /* Change the clock source. */
        ddi_write_bitfield_16(DDI0_OSC_BASE,
                              offsetof(ddi0_osc_regs_t, CTL0),
                              DDI_0_OSC_CTL0_SCLK_LF_SRC_SEL_M,
                              DDI_0_OSC_CTL0_SCLK_LF_SRC_SEL_S,
                              osc);
    }
}
