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
 * @brief           CC13x2 IEEE 802.15.4 netdev driver
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 * @}
 */

#include "cc26x2_cc13x2_rf.h"
#include "cc26xx_cc13xx_rfc_mailbox.h"

/* Overrides for CMD_PROP_RADIO_DIV_SETUP */
static uint32_t rf_prop_overrides[] =
{
    /* override_prop_common.xml
     * DC/DC regulator: In Tx, use DCDCCTL5[3:0]=0x7 (DITHER_EN=0 and IPEAK=7).
     */
    (uint32_t)0x00F788D3,
    /* override_tc146.xml
     * Tx: Configure PA ramp time, PACTL2.RC=0x3 (in ADI0, set PACTL2[4:3]=0x3)
     */
    RFC_ADI_2HALFREG_OVERRIDE(0, 16, 0x8, 0x8, 17, 0x1, 0x1),
    /* Tx: Configure PA ramping, set wait time before turning off (0x1A ticks
     of 16/24 us = 17.3 us).
     */
    RFC_HW_REG_OVERRIDE(0x6028, 0x001A),
    /* Rx: Set AGC reference level to 0x16 (default: 0x2E) */
    RFC_HW_REG_OVERRIDE(0x609C, 0x0016),
    /* Rx: Set RSSI offset to adjust reported RSSI by -1 dB (default: -2),
     * trimmed for external bias and differential configuration */
    (uint32_t)0x000188A3,
    /* Rx: Set anti-aliasing filter bandwidth to 0x8 (in ADI0, set
     * IFAMPCTL3[7:4]=0x8) */
    RFC_ADI_HALFREG_OVERRIDE(0, 61, 0xF, 0x8),
    /* TX power override
     * Tx: Set PA trim to max to maximize its output power (in ADI0,
     * set PACTL0=0xF8) */
    RFC_ADI_REG_OVERRIDE(0, 12, 0xF8),
    RFC_END_OVERRIDE
};

rfc_cmd_prop_radio_div_setup_t rf_cmd_prop_radio_div_setup =
{
    .op.command_no = 0x3807,
    .op.status = 0x0000,
    .op.next_op = NULL, /* set by us */
    .op.start_time = 0x00000000,
    .op.start_trigger.type = RFC_TRIG_NOW,
    .op.start_trigger.ena_cmd = 0x0,
    .op.start_trigger.trigger_no = 0x0,
    .op.start_trigger.past_trig = 0x0,
    .op.condition.rule = 0x1,
    .op.condition.skip_no = 0x0,
    .modulation.mod_type = 0x1,
    .modulation.deviation = 0xC8,
    .modulation.deviation_step_sz = 0x0,
    .symbol_rate.prescale = 0xF,
    .symbol_rate.rate_word = 0x20000,
    .symbol_rate.decim_mode = 0x0,
    .rx_bw = 0x59,
    .pream_conf.pream_bytes = 0x7,
    .pream_conf.pream_mode = 0x0,
    .format_conf.sw_bits = 0x18,
    .format_conf.bit_reversal = 0x0,
    .format_conf.msb_first = 0x1,
    .format_conf.fec_mode = 0x0,
    .format_conf.whiten_mode = 0x7,
    .config.front_end_mode = 0x0,
    .config.bias_mode = 0x1,
    .config.analog_cfg_mode = 0x0,
    .config.no_fs_powerup = 0x0,
    .tx_power = 0x04C0,
    .reg_override = rf_prop_overrides,
    .center_freq = 0x0393,
    .int_freq = 0x0999,
    .lo_divider = 0x05
};

rfc_cmd_fs_t rf_cmd_fs =
{
    .op.command_no = RFC_CMD_FS,
    .op.status = RFC_IDLE,
    .op.next_op = NULL, /* set by us */
    .op.start_time = 0,
    .op.start_trigger.type = RFC_TRIG_NOW,
    .op.start_trigger.ena_cmd = 0,
    .op.start_trigger.trigger_no = 0,
    .op.start_trigger.past_trig = 0,
    .op.condition.rule = RFC_COND_NEVER,
    .op.condition.skip_no = 0,
    .frequency = 0x0393, /* set by us */
    .fract_freq = 0, /* set by us */
    .synth_conf.txmode = 0,
    .synth_conf.ref_freq = 0,
    .__dummy0 = 0,
    .__dummy1 = 0,
    .__dummy2 = 0,
    .__dummy3 = 0
};

rfc_cmd_prop_tx_adv_t rf_cmd_prop_tx_adv =
{
    .op.command_no = 0x3803,
    .op.status = 0x0000,
    .op.next_op = NULL, /* set by us */
    .op.start_time = 0x00000000,
    .op.start_trigger.type = RFC_TRIG_NOW,
    .op.start_trigger.ena_cmd = 0x0,
    .op.start_trigger.trigger_no = 0x0,
    .op.start_trigger.past_trig = 0x0,
    .op.condition.rule = 0x1,
    .op.condition.skip_no = 0x0,
    .pkt_conf.fs_off = 0x0,
    .pkt_conf.use_crc = 0x1,
    .pkt_conf.crc_inc_sw = 0x0,
    .pkt_conf.crc_inc_hdr = 0x0,
    .num_hdr_bits = 0x10,
    .pkt_len = 0x0014,
    .start_conf.ext_tx_trig = 0x0,
    .start_conf.input_mode = 0x0,
    .start_conf.source = 0x0,
    .pre_trigger.type = RFC_TRIG_NOW,
    .pre_trigger.ena_cmd = 0x0,
    .pre_trigger.trigger_no = 0x0,
    .pre_trigger.past_trig = 0x0,
    .pre_time = 0x00000000,
    .sync_word = 0x0055904E,
    .pkt = 0 /* set by us */
};

rfc_cmd_prop_rx_adv_t rf_cmd_prop_rx_adv =
{
    .op.command_no = 0x3804,
    .op.status = 0x0000,
    .op.next_op = NULL, /* set by us */
    .op.start_time = 0x00000000,
    .op.start_trigger.type = RFC_TRIG_NOW,
    .op.start_trigger.ena_cmd = 0x0,
    .op.start_trigger.trigger_no = 0x0,
    .op.start_trigger.past_trig = 0x0,
    .op.condition.rule = 0x1,
    .op.condition.skip_no = 0x0,
    .pkt_conf.fs_off = 0x0,
    .pkt_conf.repeat_ok = 0x1,
    .pkt_conf.repeat_nok = 0x1,
    .pkt_conf.use_crc = 0x1,
    .pkt_conf.crc_inc_sw = 0x0,
    .pkt_conf.crc_inc_hdr = 0x0,
    .pkt_conf.end_type = 0x0,
    .pkt_conf.filter_op = 0x1,
    .rx_conf.auto_flush_ignored = 0x1,
    .rx_conf.auto_flush_crc_err = 0x1,
    .rx_conf.include_hdr = 0x0,
    .rx_conf.include_crc = 0x0,
    .rx_conf.append_rssi = 0x1,
    .rx_conf.append_timestamp = 0x0,
    .rx_conf.append_status = 0x1,
    .sync_word0 = 0x0055904E,
    .sync_word1 = 0x00000000,
    .max_pkt_len = IEEE802154G_FRAME_LEN_MAX,
    .hdr_conf.num_hdr_bits = 0x10,
    .hdr_conf.len_pos = 0x0,
    .hdr_conf.num_len_bits = 0xB,
    .addr_conf.addr_type = 0x0,
    .addr_conf.addr_size = 0x0,
    .addr_conf.addr_pos = 0x0,
    .addr_conf.num_addr = 0x0,
    .len_offset = 0xFC,
    .end_trigger.type = 0x1,
    .end_trigger.ena_cmd = 0x0,
    .end_trigger.trigger_no = 0x0,
    .end_trigger.past_trig = 0x0,
    .end_time = 0x00000000,
    .addr = 0, /* unused */
    .queue = 0, /* set by us */
    .output = 0 /* set by us */
};
