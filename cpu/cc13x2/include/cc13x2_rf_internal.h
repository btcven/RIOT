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

#ifndef CC13X2_RF_INTERNAL_H
#define CC13X2_RF_INTERNAL_H

#include "cc26xx_cc13xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: should this be moved to a more general implementation to support
 * other chips in cc26xx_cc13xx? */
/**
 * @brief   Chip type.
 */
enum {
    CHIP_TYPE_UNKNOWN = 0,
    CHIP_TYPE_CC1352P, /**< CC1352P */
    CHIP_TYPE_CC1352, /**< CC1352 */
    CHIP_TYPE_CC1312, /**< CC1312 */
    CHIP_TYPE_CC2642, /**< CC2642 */
    CHIP_TYPE_CC2652, /**< CC2652 */
};

/**
 * @brief   Get the chip type
 *
 * @return  One of the CHIP_TYPE_* values, or CHIP_TYPE_UNKNOWN if chip not
 *          supported/found.
 */
int_fast32_t cc13x2_rf_chip_type(void);

/**
 * @brief   Select radio mode
 *
 *          Currently propietary mode when using Sub-GHz and IEEE mode for
 *          2.4 GHz.
 *
 * @return  0 on success, -1 on error
 */
int_fast32_t cc13x2_rf_mode_sel(void);

void cc13x2_rf_power_up(void);
int cc13x2_rf_send_cmd(uint32_t cmd, uint32_t *result);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC13X2_RF_INTERNAL_H */

/** @}*/
