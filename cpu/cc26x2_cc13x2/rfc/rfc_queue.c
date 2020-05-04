/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         cpu_cc26xx_cc13xx
 * @{
 *
 * @file
 * @brief           CC26xx/CC13xx RF Core queue management
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#include "cc26xx_cc13xx_rfc_queue.h"

#define ENABLE_DEBUG (0)
#include "debug.h"

void rfc_data_queue_init(rfc_data_queue_t *queue, uint8_t *curr_entry)
{
    DEBUG("rfc_data_queue_init(%08lx, %08lx)\n", (uint32_t)queue,
          (uint32_t)curr_entry);

    assert(queue && curr_entry);

    /* Configure the data queue as a circular buffer */
    queue->curr_entry = curr_entry;
    queue->last_entry = NULL;
}

uint8_t *rfc_data_queue_available(rfc_data_queue_t *queue)
{
    assert(queue);

    rfc_data_entry_t *start_entry = (rfc_data_entry_t *)queue->curr_entry;
    rfc_data_entry_t *curr_entry = start_entry;

    do {
        if (curr_entry->status == RFC_DATA_ENTRY_FINISHED) {
            return (uint8_t *)curr_entry;
        }

        curr_entry = (rfc_data_entry_t *)(curr_entry->next_entry);
    } while (curr_entry != start_entry);

    return NULL;
}

void rfc_data_entry_gen_init(uint8_t *buf, const size_t buf_len,
                             const size_t lensz, uint8_t *next_entry)
{
    DEBUG("rfc_data_entry_init(%08lx, %d, %d, %08lx)\n", (uint32_t)buf, buf_len,
          lensz, (uint32_t)next_entry);

    assert(buf && lensz <= 2);
    assert(buf_len > sizeof(rfc_data_entry_t) + lensz);

    /* At the start of the buffer there's a `rfc_data_entry_t` structure,
     * we directly cast the buffer to it */
    rfc_data_entry_t *data_entry = (rfc_data_entry_t *)buf;

    data_entry->status = RFC_DATA_ENTRY_PENDING;

    /* Configure buffer as a general entry */
    data_entry->config.type = RFC_DATA_ENTRY_TYPE_GEN;

    /* Length of the length field in bytes, it's 2 byte maximum */
    data_entry->config.lensz = lensz;

    data_entry->length = buf_len - sizeof(rfc_data_entry_t);

    data_entry->next_entry = next_entry;

    DEBUG("rfc_data_entry_init: %08lx, %u, %u, %u %u\n",
          (uint32_t)data_entry->next_entry, data_entry->status,
          data_entry->config.type, data_entry->config.lensz,
          data_entry->length);
}
