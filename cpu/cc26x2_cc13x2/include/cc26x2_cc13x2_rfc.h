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
 * @brief           CC26x2/CC13x2 RF Core common functions
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifndef CC26X2_CC13X2_RFC_H
#define CC26X2_CC13X2_RFC_H

#include <stdint.h>
#include <stdbool.h>

#include "cc26xx_cc13xx_rfc_common_cmd.h"
#include "cc26xx_cc13xx_rfc_mailbox.h"
#include "cc26xx_cc13xx_rfc_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Initialize RF driver
 *
 * @param[in] radio_setup  The radio setup command.
 * @param[in] cpe_patch_fn CPE patch function, can be NULL.
 * @param[in] handler_cb   IRQ handler.
 */
void rfc_init(rfc_op_t *radio_setup, void (* cpe_patch_fn)(void),
              void ( *handler_cb)(void));

/**
 * @brief   Enable radio.
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int rfc_enable(void);

/**
 * @brief   Send a command to the RF Core.
 *
 * @param[in] op         The command to send.
 *
 * @return CMDSTA register value.
 */
uint32_t rfc_send_command(rfc_op_t *op);

/**
 * @brief   Abort the running command.
 */
void rfc_abort_command(void);

/**
 * @brief   Initialize a data queue.
 *
 * Initializes a data queue as a circular buffer with the given buffer.
 *
 * @pre (@p queue != NULL) && (@p bufs != NULL)
 *
 * @param[in] queue      The queue.
 * @param[in] curr_entry First entry in the queue.
 */
void rfc_data_queue_init(rfc_data_queue_t *queue, uint8_t *curr_entry);

/**
 * @brief   Is data available on the data queue?
 *
 * Loops over the queue to check for finished entries.
 *
 * @note The data queue must be configured as a circular buffer with
 *       @ref rfc_data_queue_init.
 *
 * @note After processing the data entry you must set the `status` field to
 *       @ref RFC_DATA_ENTRY_PENDING so the radio CPU can use it again.
 *
 * @pre @p queue != NULL
 *
 * @param[in] queue The data queue to check.
 *
 * @return uint8_t * The finished data entry.
 * @return NULL      No data available.
 */
uint8_t *rfc_data_queue_available(rfc_data_queue_t *queue);

/**
 * @brief   Initialize data entry
 *
 * @pre @p buf != NULL
 * @pre @p lensz <= 2
 * @pre @p buf_len > sizeof(@ref rfc_data_entry_t) + @p lensz
 *
 * @param[in] buf        The data entry.
 * @param[in] buf_len    The buffer length (including data entry length).
 * @param[in] lensz      Size of the length field.
 * @param[in] next_entry Next datay entry.
 */
void rfc_data_entry_gen_init(uint8_t *buf, const size_t buf_len,
                             const size_t lensz, uint8_t *next_entry);

#ifdef __cplusplus
}
#endif

#endif /* CC26X2_CC13X2_RFC_H */

/*@}*/
