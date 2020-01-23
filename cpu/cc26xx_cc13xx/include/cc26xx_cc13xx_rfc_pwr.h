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
 * @brief           CC26xx/CC13xx RFC_PWR register definitions
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifndef CC26XX_CC13XX_RFC_PWR_H
#define CC26XX_CC13XX_RFC_PWR_H

#include "cc26xx_cc13xx.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * RFC_PWR component registers
 */
typedef struct {
    reg32_t PWMCLKEN; /**< RF core clock enable */
} rfc_pwr_regs_t;

/**
 * @name RFC_PWR registers fields values.
 *
 * @{
 */
#define PWMCLKEN_RFCTRC                    0x00000400
#define PWMCLKEN_FSCA                      0x00000200
#define PWMCLKEN_PHA                       0x00000100
#define PWMCLKEN_RAT                       0x00000080
#define PWMCLKEN_RFERAM                    0x00000040
#define PWMCLKEN_RFE                       0x00000020
#define PWMCLKEN_MDMRAM                    0x00000010
#define PWMCLKEN_MDM                       0x00000008
#define PWMCLKEN_CPERAM                    0x00000004
#define PWMCLKEN_CPE                       0x00000002
#define PWMCLKEN_RFC                       0x00000001
/** @} */

/** @ingroup cpu_specific_peripheral_memory_map
  * @{
  */
#define RFC_PWR_BASE        (PERIPH_BASE + 0x40000) /**< RFC_PWR base address */
#define RFC_PWR_NONBUF_BASE (PERIPH_NONBUF_BASE + 0x40000) /**< RFC_PWR non-buffered base address */
/** @} */

#define RFC_PWR           ((rfc_pwr_regs_t *) (RFC_PWR_BASE)) /**< RFC_PWR register bank */
#define RFC_PWR_NONBUF    ((rfc_pwr_regs_t *) (RFC_PWR_NONBUF_BASE)) /**< RFC_PWR register bank */

#endif /* CC26XX_CC13XX_RFC_PWR_H */

/*@}*/
