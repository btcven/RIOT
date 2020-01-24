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

#ifndef CC13X2_RF_H
#define CC13X2_RF_H

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CUSTOMER_ADDR0 (CCFG->IEEE_MAC_0) /**< IEEE 802.15.4 address of customer part 1 */
#define CUSTOMER_ADDR1 (CCFG->IEEE_MAC_1) /**< IEEE 802.15.4 address of customer part 2 */

#define FACTORY_ADDR0 (CCFG->IEEE_MAC_0) /**< Factory generated IEEE 802.15.4 address part 1 */
#define FACTORY_ADDR1 (CCFG->IEEE_MAC_1) /**< Factory generated IEEE 802.15.4 address part 2 */

/**
 * @brief Setup RF netdev interface
 */
void cc13x2_rf_setup(void);

/**
 * @brief Get IEEE 802.15.4 long address
 */
uint64_t cc13x2_rf_get_addr_long(void);

/**
 * @brief Get IEEE 802.15.4 short address
 */
uint16_t cc13x2_rf_get_addr_short(void);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC13X2_RF_H */

/** @}*/
