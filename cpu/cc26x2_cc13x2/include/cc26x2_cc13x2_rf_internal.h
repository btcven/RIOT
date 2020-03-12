/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         cpu_cc26x2_cc13x2
 * @{
 *
 * @file
 * @brief           CC26x2, CC13x2 RF driver
 */

#ifndef CC26X2_CC13X2_RF_INTERNAL_H
#define CC26X2_CC13X2_RF_INTERNAL_H

#include <ti/drivers/rf/RF.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   The different front-end modes the CC13xx/CC26xx devices support.
 *
 * The front-end mode can be configured independently of the bias mode. The two
 * types of modes are as follows:
 *
 * - Differential: Both RF_P and RF_N are used as a differential RF interface.
 * - Single ended: Either the RF_P pin or the RF_N pin is used as the RF path.
 *
 *  @{
 */
#define RF_FRONT_END_MODE_DIFFERENTIAL     (0) /**< Differential mode */
#define RF_FRONT_END_MODE_SINGLE_ENDED_RFP (1) /**< Single-ended RF_P */
#define RF_FRONT_END_MODE_SINGLE_ENDED_RFN (2) /**< Single-ended RF_N */
/** @} */

/**
 * @brief    Front-end mode for Sub-GHz
 */
#ifndef RF_SUB_GHZ_FRONT_END_MODE
#define RF_SUB_GHZ_FRONT_END_MODE RF_FRONT_END_MODE_DIFFERENTIAL
#endif

/**
 * \name    The different bias modes the CC13xx/CC26xx devices support.
 *
 * The bias mode can be configured independently of the front-end mode. The two
 * different modes are as follows:
 *
 * - Internal bias: the LNA is biased by an internal bias.
 * - External bias: the LNA is biased by an external bias.
 *
 * @{
 */
#define RF_BIAS_MODE_INTERNAL (0) /**< Internal bias */
#define RF_BIAS_MODE_EXTERNAL (1) /**< External bias */
/** @} */

/**
 * @brief   Bias mode for Sub-GHz
 */
#ifndef RF_SUB_GHZ_BIAS_MODE
#define RF_SUB_GHZ_BIAS_MODE RF_BIAS_MODE_EXTERNAL
#endif

#define PROP_MODE_CENTER_FREQ (0x0393)
#define PROP_MODE_LO_DIVIDER  (5)

/**
 * @brief   Initialize RF driver
 *
 * @return  0 Succeed
 * @return -1 RF initialization failed
 */
int cc26x2_cc13x2_rf_init(void);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26X2_CC13X2_RF_INTERNAL_H */
