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
 * @brief           CC13x2 DDI support code
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 * @}
 */

#include "cc13x2_ddi.h"

uint16_t ddi_read_bitfield_16(uint32_t base,
                              uint32_t reg,
                              uint32_t mask,
                              uint32_t shift)
{
    /* Calculate the register address */
    uint32_t regaddr = (base + reg) + DDI_DIR;

    /* Adjust for target bit in high half of the word */
    if (shift >= 16) {
        shift = shift - 16;
        regaddr += 2;
        mask = mask >> 16;
    }

    /* Read the register */
    uint16_t data = *(volatile uint16_t *)regaddr;

    /* Mask data and shift into place */
    data &= mask;
    data >>= shift;

    return data;
}

void ddi_write_bitfield_16(uint32_t base,
                           uint32_t reg,
                           uint32_t mask,
                           uint32_t shift,
                           uint16_t data)
{
    /* 16-bit target is on 32-bit boundary so double offset. */
    uint32_t regaddr = base + (reg << 1) + DDI_MASK16B;

    /* Adjust for target bit in high half of the word */
    if (shift >= 16) {
        shift = shift - 16;
        regaddr += 4;
        mask = mask >> 16;
    }

    /* Shift data in to position */
    uint32_t wrdata = data << shift;

    /* Write data */
    *(volatile uint32_t *)regaddr = (mask << 16) | wrdata;
}
