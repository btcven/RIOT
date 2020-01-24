/*
 * Copyright (C)    2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         boards_cc1312_launchpad
 * @{
 *
 * @file
 * @brief           Radio configuration for TI CC1312 LaunchPad
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "cpu.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Overrides for CMD_PROP_RADIO_DIV_SETUP */
static uint32_t rf_prop_overrides[] __attribute__ ((aligned(4))) =
{
    /* override_prop_common.xml
     * DC/DC regulator: In Tx, use DCDCCTL5[3:0]=0x7 (DITHER_EN=0 and IPEAK=7). */
    (uint32_t)0x00F788D3,
    /* override_tc106.xml
     * Tx: Configure PA ramp time, PACTL2.RC=0x3 (in ADI0, set PACTL2[4:3]=0x3) */
    ADI_2HALFREG_OVERRIDE(0,16,0x8,0x8,17,0x1,0x1),
    /* Rx: Set AGC reference level to 0x1A (default: 0x2E) */
    HW_REG_OVERRIDE(0x609C,0x001A),
    /* Rx: Set RSSI offset to adjust reported RSSI by -1 dB (default: -2),
     * trimmed for external bias and differential configuration */
    (uint32_t)0x000188A3,
    /* Rx: Set anti-aliasing filter bandwidth to 0xD (in ADI0, set
     * IFAMPCTL3[7:4]=0xD) */
    ADI_HALFREG_OVERRIDE(0,61,0xF,0xD),
    /* Tx: Set wait time before turning off ramp to 0x1A (default: 0x1F) */
    HW_REG_OVERRIDE(0x6028,0x001A),
#if 0 /*RF_TXPOWER_BOOST_MODE*/
    // TX power override
    // Tx: Set PA trim to max to maximize its output power (in ADI0, set PACTL0=0xF8)
    ADI_REG_OVERRIDE(0,12,0xF8),
#endif
    (uint32_t)0xFFFFFFFF,
};

static rfc_cmd_prop_radio_div_setup_t rf_cmd_prop_radio_div_setup __attribute__ ((aligned(4))) =
{
    .command_no = CMD_PROP_RADIO_DIV_SETUP,
    .status = IDLE,
    .next_op = 0,
    .start_time = 0x00000000,
    .start_trigger.trigger_type = TRIG_NOW,
    .start_trigger.ena_cmd = 0x0,
    .start_trigger.trigger_no = 0x0,
    .start_trigger.past_trig = 0x0,
    .condition.rule = COND_NEVER,
    .condition.skip_no = 0x0,
    .modulation.mod_type = 0x1,
    .modulation.deviation = 0x64,
    .modulation.deviation_step_sz = 0x0,
    .symbolrate.prescale = 0xf,
    .symbolrate.rateword = 0x8000,
    .symbolrate.decimmode = 0x0,
    .rxbw = 0x52,
    .preamconf.preambytes = 0x7,
    .preamconf.preammode = 0x0,
    .formatconf.swbits = 0x18,
    .formatconf.bitreversal = 0x0,
    .formatconf.msbfirst = 0x1,
    .formatconf.fecmode = 0x0,
    .formatconf.whitenmode = 0x7,
    .config.frontendmode = 0x0,
    .config.biasmode = 0x0,
    .config.analogcfgmode = 0x0,
    .config.nofspowerup = 0x0,
    .txpower = 0xcc14,
    .regoverride = rf_prop_overrides,
    .centerfreq = 0x0393,
    .intfreq = 0x8000,
    .lodivider = 0x05,
};

#define CC13X2_RF_MODE       0x00 /**< RF mode */
#define CC13X2_RF_LO_DIVIDER 0x05 /**< LO divider */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
