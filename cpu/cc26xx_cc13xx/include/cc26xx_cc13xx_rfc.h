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
 * @brief Proprietary Mode Radio Setup Command for All Frequency Bands
 */
typedef struct {
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
    struct {
        uint16_t mod_type:3; /**< 0h = FSK
                                  1h = GFSK
                                  2h = OOK */
        uint16_t deviation:11; /**< deviation (specified in number of steps, with
                                    step size given by deviation_step_sz) */
        uint16_t deviation_step_sz:2; /**< Deviation step size
                                           0h = 250 Hz
                                           1h = 1000 Hz
                                           2h = 15.625 Hz
                                           3h = 62.5 Hz */
    } modulation; /**< modulation type */
    struct {
        uint32_t prescale:8; /**< prescaler value */
        uint32_t rateword:21; /**< rate word */
        uint32_t decimmode:3; /**< 0h = Use automatic PDIF decimation
                                    1h = Force PDIF decimation to 0
                                    3h = Force PDIF decimation to 1
                                    5h = Force PDIF decimation to 2 */
    } symbolrate; /**< symbol rate setting */
    uint8_t rxbw; /**< receiver bandwidth */
    struct {
        uint8_t preambytes:6; /**< 0h = 1 preamble bit
                                   1h--10h = Number of preamble bytes,
                                   12h, 14h, ..., 1Eh = Number of preamble bytes,
                                   1Fh = 4 preamble bits
                                   20h = 32 preamble bytes */
        uint8_t preammode:2; /**< 0h = Send 0 as the first preamble bit
                                   1h = Send 1 as the first preamble bit
                                   2h = Send same first bit in preamble and sync word
                                   3h = Send different first bit in preamble and sync word */
    } preamconf; /**< preamble configuration */
    struct {
        uint16_t swbits:6; /**< number of sync word bits (8--32) */
        uint16_t bitreversal:1; /**< 0h = Use positive deviation for 1
                                     1h = Use positive deviation for 0 */
        uint16_t msbfirst:1; /**< 0h = Least significant bit transmitted first
                                  1h = Most significant bit transmitted first */
        uint16_t fecmode:4; /**< Select coding
                                 0h = Uncoded binary modulation
                                 10h = Manchester coded binary modulation */
        uint16_t :1;
        uint16_t whitenmode:3; /**< 0h = No whitening
                                    1h = CC1101/CC2500 compatible whitening
                                    2h = PN9 whitening without byte reversal
                                    3h = Reserved
                                    4h = No whitener, 32-bit IEEE 802.15.4g compatible CRC
                                    5h = IEEE 802.15.4g compatible whitener and 32-bit CRC
                                    6h = No whitener, dynamically IEEE 802.15.4g compatible 16-bit
                                         or 32-bit CRC
                                    7h = Dynamically IEEE 802.15.4g compatible whitener and 16-bit
                                         or 32-bit CRC */
    } formatconf; /**< format configuration */
    struct {
        uint16_t frontendmode:3; /**< 0x00 = Differential mode
                                      0x01 = Single-ended mode RFP
                                      0x02 = Single-ended mode RFN
                                      0x05 = Single-ended mode RFP with external frontend control on
                                      RF pins (RFN and RXTX)
                                      0x06 = Single-ended mode RFN with external frontend control on
                                      RF pins (RFP and RXTX) */
        uint16_t biasmode:1; /**< 0h = Internal bias
                                  1h = External bias */
        uint16_t analogcfgmode:6; /**< 0x00 = Write analog configuration.
                                       Required first time after boot and when changing
                                       frequency band or front-end configuration
                                       0x2D = Keep analog configuration.
                                       May be used after standby or when changing mode with the same
                                       frequency band and front-end configuration */
        uint16_t nofspowerup:1; /**< 0h = Power up frequency synth
                                     1h = Do not power up frequency synth */
    } config; /**< configuration options */
    uint16_t txpower; /**< transmit power */
    uint32_t* regoverride; /**< pointer to a list of hardware and configuration registers to
                                override. If NULL, no override is used. */
    uint16_t centerfreq; /**< center frequency of the frequency band used, in MHz; used for
                              calculating some internal TX and RX parameters. For a single
                              channel RF system, this should be set equal to the RF frequency
                              used. For a multi channel RF system (e.g. frequency hopping spread
                              spectrum), this should be set equal to the center frequency of the
                              frequency band used. */
    int16_t intfreq; /**< intermediate frequency to use for RX, in MHz on 4.12 signed format. TX
                          will use same intermediate frequency if supported, otherwise 0.
                          0x8000 = Use default. */
    uint8_t lodivider; /**< LO frequency divider setting to use.
                            Supported values: 0, 2, 4, 5, 6, 10, 12, 15, and 30 */
} __attribute__ ((aligned(4))) rfc_cmd_prop_radio_div_setup_t;


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

#define COND_ALWAYS         0
#define COND_NEVER          1
#define COND_STOP_ON_FALSE  2
#define COND_STOP_ON_TRUE   3
#define COND_SKIP_ON_FALSE  4
#define COND_SKIP_ON_TRUE   5

#define TRIG_NOW            0
#define TRIG_NEVER          1
#define TRIG_ABSTIME        2
#define TRIG_REL_SUBMIT     3
#define TRIG_REL_START      4
#define TRIG_REL_PREVSTART  5
#define TRIG_REL_FIRSTSTART 6
#define TRIG_REL_PREVEND    7
#define TRIG_REL_EVT1       8
#define TRIG_REL_EVT2       9
#define TRIG_EXTERNAL       10
#define TRIG_PAST_BM        0x80

#define IDLE                0x0000
#define PENDING             0x0001
#define ACTIVE              0x0002
#define SKIPPED             0x0003

#define DONE_OK             0x0400
#define DONE_COUNTDOWN      0x0401
#define DONE_RXERR          0x0402
#define DONE_TIMEOUT        0x0403
#define DONE_STOPPED        0x0404
#define DONE_ABORT          0x0405
#define DONE_FAILED         0x0406

#define ERROR_PAST_START    0x0800
#define ERROR_START_TRIG    0x0801
#define ERROR_CONDITION     0x0802
#define ERROR_PAR           0x0803
#define ERROR_POINTER       0x0804
#define ERROR_CMDID         0x0805

#define ERROR_WRONG_BG      0x0806
#define ERROR_NO_SETUP      0x0807
#define ERROR_NO_FS         0x0808
#define ERROR_SYNTH_PROG    0x0809
#define ERROR_TXUNF         0x080A
#define ERROR_RXOVF         0x080B
#define ERROR_NO_RX         0x080C
#define ERROR_PENDING       0x080D

/**
 * @brief Macro for ADI half-size value-mask combination
 */
#define ADI_VAL_MASK(addr, mask, value) \
    (((addr) & 1) ? (((mask) & 0x0F) | (((value) & 0x0F) << 4)) : \
    ((((mask) & 0x0F) << 4) | ((value) & 0x0F)))

/**
 * @brief 32-bit write of 16-bit value
 */
#define HW_REG_OVERRIDE(addr, val) \
    ((((uintptr_t) (addr)) & 0xFFFC) | ((uint32_t)(val) << 16))

/**
 * @brief ADI register, half-size read-modify-write
 */
#define ADI_HALFREG_OVERRIDE(adino, addr, mask, val) \
    (2 | (ADI_VAL_MASK(addr, mask, val) << 16) | \
    (((addr) & 0x3F) << 24) | (1U << 30) | (((adino) ? 1U : 0) << 31))

/**
 * @brief ADI registers, half-size read-modify-write
 */
#define ADI_2HALFREG_OVERRIDE(adino, addr, mask, val, addr2, mask2, val2) \
    (2                                      | \
    (ADI_VAL_MASK(addr2, mask2, val2) << 2) | \
    (((addr2) & 0x3F) << 10)                | \
    (ADI_VAL_MASK(addr, mask, val) << 16)   | \
    (((addr) & 0x3F) << 24)                 | \
    (1U << 30)                              | \
    (((adino) ? 1U : 0) << 31))

#define CMD_PROP_RADIO_DIV_SETUP                 0x3807
#define CMD_PING                                 0x0406
/** @} */

#endif /* CC26XX_CC13XX_RFC_H */

/*@}*/
