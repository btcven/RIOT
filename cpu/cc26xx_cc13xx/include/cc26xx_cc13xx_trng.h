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
 * @brief           CC26xx/CC13xx MCU I/O register definitions
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifndef CC26XX_CC13XX_TRNG_H
#define CC26XX_CC13XX_TRNG_H

#include "cc26xx_cc13xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   TRNG registers
 */
typedef struct {
    reg32_t OUT0; /**< Random Number Lower Word Readout Value */
    reg32_t OUT1; /**< Random Number Upper Word Readout Value */
    reg32_t IRQFLAGSTAT; /**< Interrupt Status */
    reg32_t IRQFLAGMASK; /**< Interrupt Mask */
    reg32_t IRQFLAGCLR; /**< Interrupt Flag Clear */
    reg32_t CTL; /**< Control */
    reg32_t CFG0; /**< Configuration 0 */
    reg32_t ALARMCNT; /**< Alarm Control */
    reg32_t FROEN; /**< FRO Enable */
    reg32_t FRODETUNE; /**< FRO De-tune Bit */
    reg32_t ALARMMASK; /**< Alarm Event */
    reg32_t ALARMSTOP; /**< Alarm Shutdown */
    reg32_t LFSR0; /**< LFSR Readout Value */
    reg32_t LFSR1; /**< LFSR Readout Value */
    reg32_t LFSR2; /**< LFSR Readout Value */
    reg32_t __reserved0[0xF]; /**< Reserved */
    reg32_t HWOPT; /**< TRNG Engine Options Information */
    reg32_t HWVER0; /**< HW Version 0 */
    reg32_t __reserved1[0x7D7]; /**< Reserved */
    reg32_t IRQSTATMASK; /**< Interrupt Status After Masking */
    reg32_t __reserved2[0x2]; /**< Reserved */
    reg32_t HWVER1; /**< HW Version 1 */
    reg32_t __reserved3[0x3]; /**< Reserved */
    reg32_t IRQSET; /**< Interrupt Set */
    reg32_t SWRESET; /**< SW Reset Control */
    reg32_t __reserved4[0x2];
    reg32_t IRQSTAT; /**< Interrupt Status */
} trng_regs_t;

/**
 * @name    TRNG register values
 * @{
 */
#define TRNG_IRQFLAGCLR_SHUTDOWN_OVF 0x00000002
#define TRNG_IRQFLAGCLR_RDY          0x00000001
/** @} */

/**
 * @ingroup cpu_specific_peripheral_memory_map
 * @{
 */
/**
 * @brief   TRNG base address
 */
#define TRNG_BASE           (PERIPH_BASE + 0x28000)
/** @} */

/**
 * @brief   TRNG register bank
 */
#define TRNG                 ((trng_regs_t *) (TRNG_BASE))

#ifdef __cplusplus
}
#endif

#endif /* CC26XX_CC13XX_TRNG_H */
/** @} */
