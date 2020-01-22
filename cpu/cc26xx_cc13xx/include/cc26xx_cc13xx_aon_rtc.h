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
 * @brief           CC26xx/CC13xx AON_RTC register definitions
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifndef CC26XX_CC13XX_AON_RTC_H
#define CC26XX_CC13XX_AON_RTC_H

#include "cc26xx_cc13xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * AON_RTC registers
 */
typedef struct {
    reg32_t CTL; /**< control */
    reg32_t EVFLAGS; /**< event flags */
    reg32_t SEC; /**< second counter value, integer part */
    reg32_t SUBSEC; /**< second counter value, fractional part */
    reg32_t SUBSECINC; /**< subseconds increment */
    reg32_t CHCTL; /**< channel configuration */
    reg32_t CH0CMP; /**< channel 0 compare value */
    reg32_t CH1CMP; /**< channel 1 compare value */
    reg32_t CH2CMP; /**< channel 2 compare value */
    reg32_t CH2CMPINC; /**< channel 2 compare value auto-increment */
    reg32_t CH1CAPT; /**< channel 1 capture value */
    reg32_t SYNC; /**< AON synchronization */
#if CPU_VARIANT_X2
    reg32_t TIME; /**< current counter value */
    reg32_t SYNCLF; /**< syncrhonization to SCLK_LF */
#endif
} aon_rtc_regs_t;

/**
 * @name CTL register fields
 * @{
 */

/**
 * @brief RTC_UPD enable
 *
 * @details 0: RTC_UPD signal is forced to 0
 *          1: RTC_UPD signal is toggling @16 kHz
 */
#define CTL_RTC_UPD_EN    (0x00000002)
/** @} */

/** @ingroup cpu_specific_peripheral_memory_map
  * @{
  */
#define AON_RTC_BASE      (PERIPH_BASE + 0x90000) /**< AON_RTC base address */
/** @} */

#define AON_RTC           ((aon_rtc_regs_t *) (AON_RTC_BASE)) /**< AON_RTC register bank */

#ifdef __cplusplus
}
#endif

#endif /* CC26XX_CC13XX_AON_RTC_H */

/*@}*/
