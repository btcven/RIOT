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
 * @brief           CC26x2/CC13x2 IEEE 802.15.4 netdev driver
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifndef CC26X2_CC13X2_RF_H
#define CC26X2_CC13X2_RF_H

#include <stdbool.h>

#include "cc26xx_cc13xx_rfc_mailbox.h"
#include "cc26xx_cc13xx_rfc_common_cmd.h"
#include "cc26xx_cc13xx_rfc_prop_cmd.h"
#include "net/netdev/ieee802154.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_CC26x2_CC13X2_RF_RX_BUF_NUMOF
/**
 * @brief   Number of receive buffers
 */
#define CONFIG_CC26x2_CC13X2_RF_RX_BUF_NUMOF (4)
#endif

/**
 * @brief   CMD_SYNC_START_RAT
 *
 * Synchronously start the RAT
 */
extern rfc_cmd_sync_start_rat_t rf_cmd_sync_start_rat;

/**
 * @brief   CMD_PROP_RADIO_DIV_SETUP
 *
 * Proprietary Mode Radio Setup Command for All Frequency Bands
 */
extern rfc_cmd_prop_radio_div_setup_t rf_cmd_prop_radio_div_setup;

/**
 * @brief   CMD_FS
 *
 * Frequency Synthesizer
 */
extern rfc_cmd_fs_t rf_cmd_fs;

/**
 * @brief   CMD_PROP_TX_ADV
 *
 * Proprietary Mode Advanced Transmit Command
 */
extern rfc_cmd_prop_tx_adv_t rf_cmd_prop_tx_adv;

/**
 * @brief   CMD_PROP_RX_ADV
 *
 * Proprietary Mode Advanced Receive Command
 */
extern rfc_cmd_prop_rx_adv_t rf_cmd_prop_rx_adv;

/**
 * @brief   CMD_CLEAR_RX
 *
 * Clear the RX queue
 */
extern rfc_cmd_clear_rx_t rf_cmd_clear_rx;

extern netdev_driver_t cc26x2_cc13x2_rf_driver; /**< CC13x2 netdev driver*/

#define CC26X2_CC13X2_RF_PA_ENTRY(bias, gain, boost, coefficient) \
    ((bias) << 0) | ((gain) << 6) | ((boost) << 8) | ((coefficient) << 9)

/**
 * @brief   RF PA table entry
 */
typedef struct {
    uint8_t dbm; /**< PA entry value in dBm */
    uint16_t val; /**< Coded value for the PA entry */
} cc26x2_cc13x2_rf_pa_t;

extern cc26x2_cc13x2_rf_pa_t cc26x2_cc13x2_rf_patable[];

/**
 * @brief   IEEE 802.15.4 Sub-GHz netdev device.
 */
typedef struct {
    netdev_ieee802154_t netdev; /**< IEEE 802.15.4 network device */
    int rx_events; /**< RX events completed */
    int tx_events; /**< TX events completed */
} cc26x2_cc13x2_rf_netdev_t;

/**
 * @brief   Setup the netdev interface.
 *
 * @pre     (@p dev != NULL)
 *
 * @param[in] dev The CC13x2 netdev device.
 */
void cc26x2_cc13x2_rf_setup(cc26x2_cc13x2_rf_netdev_t *dev);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC26X2_CC13X2_RF_H */

/*@}*/
