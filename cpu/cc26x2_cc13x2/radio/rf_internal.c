/*
 * Copyright (C) 2020 Locha Mesh
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "cc26x2_cc13x2_rf_internal.h"

#include "cc26x2_cc13x2_rf_commands.h"
#include "cc26x2_cc13x2_rf_ieee802154.h"
#include "cc26x2_cc13x2_rf_queue.h"

static RF_Object _rf_prop_obj;

#define INACTIVITY_TIMEOUT (2000) /**< Inactivity timeout: 2 ms */

typedef uint16_t lensz_t;

typedef struct {
    RF_Handle handle; /**< RF driver handle */
    rfc_propRxOutput_t rx_stats; /**< RX Statistics struct */
} internal_t;

static cc26x2_cc13x2_rf_queue_t _queue;
static internal_t _radio;

static void _init_radio_parameters(rfc_CMD_PROP_RADIO_DIV_SETUP_t *cmd_radio_setup);
static void _init_transmit_parameters(rfc_CMD_PROP_TX_ADV_t *cmd_tx);
static void _init_receive_parameters(rfc_CMD_PROP_RX_ADV_t *cmd_rx);

static void _init_radio_parameters(rfc_CMD_PROP_RADIO_DIV_SETUP_t *cmd_radio_setup)
{
    cmd_radio_setup->config.frontEndMode = RF_SUB_GHZ_FRONT_END_MODE;
    cmd_radio_setup->config.biasMode = RF_SUB_GHZ_BIAS_MODE;
    cmd_radio_setup->centerFreq = RF_PROP_MODE_CENTER_FREQ;
    cmd_radio_setup->loDivider = RF_PROP_MODE_LO_DIVIDER;
}

static void _init_transmit_parameters(rfc_CMD_PROP_TX_ADV_t *cmd_tx)
{
    cmd_tx->numHdrBits = RF_IEEE802154_PHR_NUM_BYTES * 8;
    cmd_tx->syncWord = RF_IEEE802154_UNCODED_SFD_0;
}

static void _init_receive_parameters(rfc_CMD_PROP_RX_ADV_t *cmd_rx)
{
    cmd_rx->syncWord0 = RF_IEEE802154_UNCODED_SFD_0;
    cmd_rx->syncWord1 = 0x00000000;
    cmd_rx->maxPktLen = RF_IEEE802154_MAX_FRAME_LEN - RF_IEEE802154_LEN_OFFSET;
    cmd_rx->hdrConf.numHdrBits = RF_IEEE802154_PHR_NUM_BYTES * 8;
    cmd_rx->lenOffset = RF_IEEE802154_LEN_OFFSET;
    cmd_rx->pQueue = cc26x2_cc13x2_rf_queue_init(&_queue, sizeof(lensz_t));
    cmd_rx->pOutput = (uint8_t *)&_radio.rx_stats;
}

void cc26x2_cc13x2_rf_init(void)
{
    /* Initialize command parameters */
    _init_radio_parameters(&rf_cmd_prop_radio_div_setup);
    _init_transmit_parameters(&rf_cmd_prop_tx_adv);
    _init_receive_parameters(&rf_cmd_prop_rx_adv);

    /* Initialize parameters structure */
    RF_Params prop_params;
    RF_Params_init(&prop_params);

    /* Change inactivity time */
    prop_params.nInactivityTimeout = INACTIVITY_TIMEOUT;

    /* Open a handle to the driver */
    _radio.handle = RF_open(&_rf_prop_obj, &rf_prop_mode,
                            (RF_RadioSetup *)&rf_cmd_prop_radio_div_setup,
                            &prop_params);
}
