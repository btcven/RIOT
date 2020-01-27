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
 * @brief           CC13x2 DDI support code
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#include <stdint.h>

#ifndef CC13X2_DDI_H
#define CC13X2_DDI_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   DDI master instruction offsets
 *
 * @{
 */
#define DDI_DIR     0x00000000
#define DDI_SET     0x00000080
#define DDI_CLR     0x00000100
#define DDI_MASK4B  0x00000200
#define DDI_MASK8B  0x00000300
#define DDI_MASK16B 0x00000400
/** @} */

/**
 * @brief   Read a 16-bit bitfield from a DDI register
 *
 * @param   base: the base address
 * @param   reg: the register offset relative to base address
 * @param   mask: the bitfield mask
 * @param   shift: the shift amount
 *
 * @return  The bitfield data
 */
uint16_t ddi_read_bitfield_16(uint32_t base,
                              uint32_t reg,
                              uint32_t mask,
                              uint32_t shift);

/**
 * @brief   Write a 16-bit value into a DDI register using maskable write
 *
 * @param   base: the base address
 * @param   reg: the register offset relative to base address
 * @param   mask: the bitfield mask
 * @param   shift: the shift amount
 *
 */
void ddi_write_bitfield_16(uint32_t base,
                           uint32_t reg,
                           uint32_t mask,
                           uint32_t shift,
                           uint16_t data);

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC13X2_DDI_H */

/** @}*/
