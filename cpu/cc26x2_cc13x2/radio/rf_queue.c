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

#include "cc26x2_cc13x2_rf_queue.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

static void _rx_bufs_init(cc26x2_cc13x2_rf_queue_t *queue)
{
    rfc_dataEntryGeneral_t *data_entry;
    size_t i;

    for(i = 0; i < RF_RX_BUF_NUM; ++i) {
        data_entry = &(queue->bufs[i].data_entry);

        data_entry->status = DATA_ENTRY_PENDING;
        data_entry->config.type = DATA_ENTRY_TYPE_GEN;
        data_entry->config.lenSz = queue->lensz;
        data_entry->length = RF_RX_BUF_SIZE - sizeof(rfc_dataEntryGeneral_t);
        /* Point to fist entry if this is last entry, else point to next entry */
        data_entry->pNextEntry =
            ((i + 1) == RF_RX_BUF_NUM) ? queue->bufs[0].buf : queue->bufs[i + 1].buf;
    }
}

static void _rx_bufs_reset(cc26x2_cc13x2_rf_queue_t *queue)
{
    size_t i;
    for (i = 0; i < RF_RX_BUF_NUM; ++i) {
        rfc_dataEntryGeneral_t *const data_entry = &(queue->bufs[i].data_entry);

        /* Clear length bytes */
        memset(&(data_entry->data), 0x0, queue->lensz);
        /* Set status to Pending */
        data_entry->status = DATA_ENTRY_PENDING;
    }
}

dataQueue_t *cc26x2_cc13x2_rf_queue_init(cc26x2_cc13x2_rf_queue_t *queue,
                                         size_t lensz)
{
    queue->lensz = lensz;

    /* Initialize RX buffers */
    _rx_bufs_init(queue);

    /* Configure data queue as circular buffer */
    queue->data_queue.pCurrEntry = queue->bufs[0].buf;
    queue->data_queue.pLastEntry = NULL;

    /* Set current read pointer to first element */
    queue->curr_entry = &(queue->bufs[0].data_entry);

    return &queue->data_queue;
}

void cc26x2_cc13x2_rf_queue_reset(cc26x2_cc13x2_rf_queue_t *queue)
{
    _rx_bufs_reset(queue);

    /* Only need to reconfigure pCurrEntry */
    queue->data_queue.pCurrEntry = queue->bufs[0].buf;

    /* Set current read pointer to first element */
    queue->curr_entry = &(queue->bufs[0].data_entry);
}

void cc26x2_cc13x2_rf_queue_release_entry(cc26x2_cc13x2_rf_queue_t *queue)
{
    rfc_dataEntryGeneral_t *const curr_entry = queue->curr_entry;
    uint8_t *const frame_ptr = (uint8_t *)&(curr_entry->data);

    /* Clear length bytes */
    memset(frame_ptr, 0x0, queue->lensz);

    /* Set status to Pending */
    curr_entry->status = DATA_ENTRY_PENDING;

    /* Move current entry to the next entry */
    queue->curr_entry = (rfc_dataEntryGeneral_t *)(curr_entry->pNextEntry);
}
