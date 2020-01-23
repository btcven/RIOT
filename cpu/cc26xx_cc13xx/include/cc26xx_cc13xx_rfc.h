/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         cpu_cc26xx_cc13xx_definitions
 * @{
 *
 * @file
 * @brief           CC26xx/CC13xx RF Core common definitions
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifndef CC26XX_CC13XX_RFC_H
#define CC26XX_CC13XX_RFC_H

#include "cc26xx_cc13xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief A radio command
 */
typedef struct {
   uint16_t command_no; /**< the command ID number */
} rfc_command_t;

typedef struct rfc_radio_op_s rfc_radio_op_t; /**< Radio operation command */

/**
 * @brief Radio operation command
 */
struct rfc_radio_op_s {
   uint16_t command_no; /**< the command ID number */
   uint16_t status; /**< an integer telling the status of the command. */
   rfc_radio_op_t *next_op; /**< pointer to the next operation to run after this operation is done */
   uint32_t start_time; /**< absolute or relative start time */
   struct {
      uint8_t trigger_type:4; /**< the type of trigger */
      uint8_t ena_cmd:1; /**< TODO: what's this? */
      uint8_t trigger_no:2; /**< TODO: what's this? */
      uint8_t past_trig:1; /**< TODO: what's this? */
   } start_trigger; /**< identification of the trigger that starts the operation */
   struct {
      uint8_t rule:4; /**< rule for how to proceed */
      uint8_t skip_no:4; /**< number of skips + 1 if the rule involves skipping */
   } condition; /**< condiiton for running next command */
} __attribute__ ((aligned(4)));

/**
 * @name Command definitions
 *
 * @{
 */
#define COMMAND_TYPE_mask                        0x0C00
#define COMMAND_TYPE_RADIO_OP                    0x0800
#define COMMAND_TYPE_IEEE_BG_RADIO_OP            0x0800
#define COMMAND_TYPE_IEEE_FG_RADIO_OP            0x0C00

#define COMMAND_PROTOCOL_mask                    0x3000
#define COMMAND_PROTOCOL_COMMON                  0x0000
#define COMMAND_PROTOCOL_BLE                     0x1000
#define COMMAND_PROTOCOL_IEEE                    0x2000
#define COMMAND_PROTOCOL_PROP                    0x3000

#define RADIO_OP_STATUS_IDLE                     0x0000
#define RADIO_OP_STATUS_PENDING                  0x0001
#define RADIO_OP_STATUS_ACTIVE                   0x0002
#define RADIO_OP_STATUS_SKIPPED                  0x0003
#define RADIO_OP_STATUS_DONE_OK                  0x0400
#define RADIO_OP_STATUS_DONE_COUNTDOWN           0x0401
#define RADIO_OP_STATUS_DONE_RXERR               0x0402
#define RADIO_OP_STATUS_DONE_TIMEOUT             0x0403
#define RADIO_OP_STATUS_DONE_STOPPED             0x0404
#define RADIO_OP_STATUS_DONE_ABORT               0x0405
#define RADIO_OP_STATUS_ERROR_PAST_START         0x0800
#define RADIO_OP_STATUS_ERROR_START_TRIG         0x0801
#define RADIO_OP_STATUS_ERROR_CONDITION          0x0802
#define RADIO_OP_STATUS_ERROR_PAR                0x0803
#define RADIO_OP_STATUS_ERROR_POINTER            0x0804
#define RADIO_OP_STATUS_ERROR_CMDID              0x0805
#define RADIO_OP_STATUS_ERROR_NO_SETUP           0x0807
#define RADIO_OP_STATUS_ERROR_NO_FS              0x0808
#define RADIO_OP_STATUS_ERROR_SYNTH_PROG         0x0809

#define CMD_PING                                 0x0406
/** @} */

#endif /* CC26XX_CC13XX_RFC_H */

/*@}*/
