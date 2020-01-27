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
 * @brief           CC13x2 OSC support code
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#include <stdint.h>

#ifndef CC13X2_OSC_H
#define CC13X2_OSC_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   OSC clock source types
 *
 * @{
 */
#define OSC_SRC_CLK_HF 0x00000001
#define OSC_SRC_CLK_LF 0x00000004

#define OSC_RCOSC_HF   0x00000000
#define OSC_XOSC_HF    0x00000001
#define OSC_RCOSC_LF   0x00000002
#define OSC_XOSC_LF    0x00000003
/** @} */

/**
 * @brief   Get the clock input oscillator
 *
 * @param   srcclk: source clock
 *
 * @return  Clock source
 */
uint32_t osc_get_clock_source(uint32_t srcclk);

/**
 * @brief   Set clock input oscillator
 *
 * @param   srcclk: source clock
 * @param   osc: the oscillator to use as input
 */
void osc_set_clock_source(uint32_t srcclk, uint32_t osc);

/**
 * @brief   Perform the switch of the HF input source
 */
void osc_hf_source_switch(void);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC13X2_OSC_H */

/** @}*/
