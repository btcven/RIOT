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

uint64_t cc13x2_rf_get_addr_long(void)
{
    /* Check if an addr exists in the customer configuration area */
    if (!(CUSTOMER_ADDR0 == 0xFFFFFFFF) &&
        !(CUSTOMER_ADDR1 == 0xFFFFFFFF)) {
        return ((uint64_t)CUSTOMER_ADDR0 << 32) | (uint64_t)CUSTOMER_ADDR1;
    }
    else {
        return ((uint64_t)FACTORY_ADDR0 << 32) | (uint64_t)FACTORY_ADDR1;
    }
}

uint16_t cc13x2_rf_get_addr_short(void)
{
    /* Check if an addr exists in the customer configuration area */
    if (!(CUSTOMER_ADDR0 == 0xFFFFFFFF) &&
        !(CUSTOMER_ADDR1 == 0xFFFFFFFF)) {
        return (uint16_t)(CUSTOMER_ADDR0 >> 16);
    }
    else {
        return (uint16_t)(FACTORY_ADDR0 >> 16);
    }
}
