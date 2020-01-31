/*
 *  Copyright (c) 2018, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

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
 * @brief           CC13x2 IEEE 802.15.4 netdev driver
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifndef CC13X2_RF_INTERNAL_H
#define CC13X2_RF_INTERNAL_H

#include <stdint.h>
#include <stddef.h>

#include "net/ieee802154.h"
#include "net/netdev/ieee802154.h"

/**
 * @brief   (IEEE 802.15.4-2006) PSDU.FCF.frameType
 */
#define IEEE802154_FRAME_TYPE_MASK 0x7

/**
 * @brief   (IEEE 802.15.4-2006) frame type: ACK
 */
#define IEEE802154_FRAME_TYPE_ACK 0x2

/**
 * @brief   (IEEE 802.15.4-2006) PSDU.FCF.bAR
 */
#define IEEE802154_ACK_REQUEST (1 << 5)

/**
 * @brief   (IEEE 802.15.4-2006) PSDU.sequenceNumber
 */
#define IEEE802154_DSN_OFFSET 2

/**
 * @brief   (IEEE 802.15.4-2006) macMinBE
 */
#define IEEE802154_MAC_MIN_BE 1

/**
 * @brief   (IEEE 802.15.4-2006) macMaxBE
 */
#define IEEE802154_MAC_MAX_BE 5

/**
 * @brief   (IEEE 802.15.4-2006) macMaxCSMABackoffs
 */
#define IEEE802154_MAC_MAX_CSMA_BACKOFFS 4

/**
 * @brief   (IEEE 802.15.4-2006) macMaxFrameRetries
 */
#define IEEE802154_MAC_MAX_FRAMES_RETRIES 3

/**
 * @brief   (IEEE 802.15.4-2006 7.4.1) MAC constants
 */
#define IEEE802154_A_UINT_BACKOFF_PERIOD 20

/**
 * @brief   (IEEE 802.15.4-2006 6.4.1) PHY constants
 */
#define IEEE802154_A_TURNAROUND_TIME 12

/**
 * @brief   (IEEE 802.15.4-2006 6.4.2) PHY PIB attribute, specifically the
 *          O-QPSK PHY
 */
#define IEEE802154_PHY_SHR_DURATION 10

/**
 * @brief   (IEEE 802.15.4-2006 6.4.2) PHY PIB attribute, specifically the
 *          O-QPSK PHY
 */
#define IEEE802154_PHY_SYMBOLS_PER_OCTET 2

/**
 * @brief   (IEEE 802.15.4-2006 7.4.2) macAckWaitDuration PIB attribute
 */
#define IEEE802154_MAC_ACK_WAIT_DURATION \
    (IEEE802154_A_UINT_BACKOFF_PERIOD +  \
     IEEE802154_A_TURNAROUND_TIME +      \
     IEEE802154_PHY_SHR_DURATION +       \
     (6 * IEEE802154_PHY_SYMBOLS_PER_OCTET))

/**
 * @brief   (IEEE 802.15.4-2006 6.5.3.2) O-QPSK symbol rate
 */
#define IEEE802154_SYMBOLS_PER_SEC 62500

#if PROP_PHY == 1
/**
 * @brief This enum represents the state of a radio.
 *
 * Initially, a radio is in the Disabled state.
 *
 * The following are valid radio state transitions for the cc13x2:
 *
 *                                    (Radio ON)
 *  +----------+  Enable()  +-------+  Receive()   +---------+   Transmit()   +----------+
 *  |          |----------->|       |------------->|         |--------------->|          |
 *  | Disabled |            | Sleep |              | Receive |                | Transmit |
 *  |          |<-----------|       |<-------------|         |<---------------|          |
 *  +----------+  Disable() |       |   Sleep()    |         | AckFrame RX or +----------+
 *                          |       | (Radio OFF)  +---------+ sTxCmdChainDone == true
 *                          +-------+
 *
 * | state            | description                                        |
 * |------------------|----------------------------------------------------|
 * | Disabled         | The rfcore powerdomain is off and the RFCPE is off |
 * | Sleep            | The RFCORE PD is on, and the RFCPE is in PROP mode |
 * | Receive          | The RFCPE is running a CMD_PROP_RX_ADV             |
 * | Transmit         | The RFCPE is running a transmit command string     |
 * | TransmitComplete | The transmit command string has completed          |
 */
typedef enum {
    cc13x2_stateDisabled = 0, /**< Disabled, radio powered off */
    cc13x2_stateSleep, /**< Sleep state, awaiting for actions */
    cc13x2_stateReceive, /**< Receive state */
    cc13x2_stateTransmit, /**< Transmitting packets */
} cc13x2_PropPhyState_t;

extern volatile cc13x2_PropPhyState_t _cc13x2_rf_prop_state;

void cc13x2_rf_prop_init(void);

int_fast8_t cc13x2_rf_prop_enable(void);
int_fast8_t cc13x2_rf_prop_disable(void);

int8_t cc13x2_rf_prop_get_txpower(void);
int_fast8_t cc13x2_rf_prop_set_txpower(int8_t power);

int8_t cc13x2_rf_prop_get_rssi(void);
int_fast8_t cc13x2_rf_prop_rx_start(void);
int_fast8_t cc13x2_rf_prop_rx_stop(void);
uint8_t cc13x2_rf_prop_get_chan(void);
void cc13x2_rf_prop_set_chan(uint16_t channel);
void cc13x2_rf_prop_get_ieee_eui64(uint8_t *aIeeeEui64);
void cc13x2_rf_prop_irq_set_handler(void(*handler)(void *), void * arg);
int cc13x2_rf_prop_recv(void *buf, size_t len, netdev_ieee802154_rx_info_t *rx_info);
int cc13x2_rf_prop_recv_avail(void);
int cc13x2_rf_prop_send(const iolist_t *iolist);
void cc13x2_rf_prop_set_pan(uint16_t aPanid);
uint16_t cc13x2_rf_prop_get_pan(void);

unsigned cc13x2_rf_prop_irq_is_enabled(unsigned irq);
void cc13x2_rf_prop_irq_enable(unsigned irq);
void cc13x2_rf_prop_irq_disable(unsigned irq);
unsigned cc13x2_rf_prop_get_flags(void);
#endif

#if IEEE_PHY == 1
/* TODO: IEEE PHY state */
#endif

#endif /* CC13X2_RF_INTERNAL_H */
/** @} */
