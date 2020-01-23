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

void cc13x2_rf_power_up(void);
int cc13x2_rf_send_cmd(uint32_t cmd, uint32_t *result);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC13X2_RF_INTERNAL_H */

/** @}*/
