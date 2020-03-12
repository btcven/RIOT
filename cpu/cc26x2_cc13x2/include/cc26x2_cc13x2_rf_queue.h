/*
 * Copyright (c) 2018, Texas Instruments Incorporated - http://www.ti.com/
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * @{
 *
 * @brief   Implementation of the CC13xx/CC26xx RF data queue.
 *
 * @author  Edvard Pettersen <e.pettersen@ti.com>
 * @author  Jean Pierre Dudey <jeandudey@hotmail.com>
 * @}
 */

#ifndef CC26X2_CC13X2_RF_QUEUE_H
#define CC26X2_CC13X2_RF_QUEUE_H

#include <driverlib/rf_mailbox.h>
#include <driverlib/rf_data_entry.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Number of RX buffers
 */
#ifndef RF_RX_BUF_NUM
#define RF_RX_BUF_NUM (4)
#endif

#ifndef RF_RX_BUF_SIZE
#define RF_RX_BUF_SIZE (125)
#endif

/**
 * @brief   Receive buffer entries with room for 1 IEEE 802.15.4 frame in each
 */
typedef union {
    rfc_dataEntryGeneral_t data_entry; /**< Data entry */
    uint8_t buf[RF_RX_BUF_SIZE]; /**< Data buffer */
} cc26x2_cc13x2_rx_buf_t __attribute__ ((__aligned__(4)));

/**
 * @brief   RF receive data queue
 */
typedef struct {
    cc26x2_cc13x2_rx_buf_t bufs[RF_RX_BUF_NUM]; /**< RX bufs */
    dataQueue_t data_queue; /**< RFC data queue object */
    rfc_dataEntryGeneral_t *curr_entry; /**< Current data entry in use by RF */
    size_t lensz; /**< Size in bytes of length field in data entry */
} cc26x2_cc13x2_rf_queue_t;

dataQueue_t *cc26x2_cc13x2_rf_queue_init(cc26x2_cc13x2_rf_queue_t *queue, size_t lensz);
void cc26x2_cc13x2_rf_queue_reset(cc26x2_cc13x2_rf_queue_t *queue);
void cc26x2_cc13x2_rf_queue_release_entry(cc26x2_cc13x2_rf_queue_t* queue);

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#endif /* CC26X2_CC13X2_RF_QUEUE_H */
