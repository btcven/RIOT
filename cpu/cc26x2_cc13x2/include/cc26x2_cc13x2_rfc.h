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
 * @param[in] cpe_patch_fn CPE patch function, can be NULL.
 * @param[in] handler_cb   IRQ handler.
 */
void cc26x2_cc13x2_rfc_init(void (* cpe_patch_fn)(void),
                            void ( *handler_cb)(void));

/**
 * @brief   Power on the radio.
 *
 *  - Switches the high frequency clock to the xosc crystal on
 *  CC26X2/CC13X2.
 *  - Powers on the radio core power domain
 *  - Enables the radio core power domain
 *
 * @return 0 on success.
 * @return -1 on failure.
 */
int cc26x2_cc13x2_rfc_power_on(void);

/**
 * @brief   Get last command sent to the RF Core.
 *
 * @return Pointer to last command.
 */
rfc_op_t *cc26x2_cc13x2_rfc_last_cmd(void);

/**
 * @brief   Send a command to the RF Core.
 *
 * @param[in] op The command to send.
 *
 * @return CMDSTA register value.
 */
uint32_t cc26x2_cc13x2_rfc_send_cmd(rfc_op_t *op);

/**
 * @brief   Abort the running command.
 */
void cc26x2_cc13x2_rfc_abort_cmd(void);

/**
 * @brief   Is data available on the data queue?
 *
 * Loops over the queue to check for finished entries.
 *
 * @note The data queue must be configured as a circular buffer (no last entry).
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
uint8_t *cc26x2_cc13x2_rfc_queue_recv(rfc_data_queue_t *queue);

#ifdef __cplusplus
}
#endif

#endif /* CC26X2_CC13X2_RFC_H */

/*@}*/
