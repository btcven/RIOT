/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup         cpu_cc13x2_definitions
 * @{
 *
 * @file
 * @brief           CC13x2 ROM support code
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#include <stdint.h>

#ifndef CC13X2_ROM_H
#define CC13X2_ROM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief  ROM Hard-API function interface types
 *
 * @{
 */
typedef uint32_t (* func_crc32_t)(uint8_t *, uint32_t, uint32_t);
typedef uint32_t (* func_getflsize_t)(void);
typedef uint32_t (* func_getchipid_t)(void);
typedef uint32_t (* func_reserved1_t)(uint32_t);
typedef uint32_t (* func_reserved2_t)(void);
typedef uint32_t (* func_reserved3_t)(uint8_t *, uint32_t, uint32_t);
typedef void (* func_resetdev_t)(void);
typedef uint32_t (* func_fletcher32_t)(uint16_t *, uint16_t, uint16_t);
typedef uint32_t (* func_minval_t)(uint32_t *, uint32_t);
typedef uint32_t (* func_maxval_t)(uint32_t *, uint32_t);
typedef uint32_t (* func_meanval_t)(uint32_t *, uint32_t);
typedef uint32_t (* func_stddval_t)(uint32_t *, uint32_t);

typedef void (* func_hf_source_safe_switch_t)(void);
typedef void (* func_reserved4_t)(uint32_t);
typedef void (* func_reserved5_t)(uint32_t);
typedef void (* func_compain_t)(uint8_t);
typedef void (* func_comparef_t)(uint8_t);
typedef void (* func_adccompbin_t)(uint8_t);
typedef void (* func_dacvref_t)(uint8_t);
/** @} */

/**
 * @brief   ROM Hard-API access table type
 */
typedef struct {
    func_crc32_t crc32; /**< CRC32 */
    func_getflsize_t flashgetsize; /**< Get flash size */
    func_getchipid_t getchipid; /**< Get chip id */
    func_reserved1_t reservedlocation1; /**< meh */
    func_reserved2_t reservedlocation2; /**< meh */
    func_reserved3_t reservedlocation3; /**< meh */
    func_resetdev_t resetdevice; /**< Reset device */
    func_fletcher32_t fletcher32; /**< TODO: ?? */
    func_minval_t minvalue; /**< TODO: ?? */
    func_maxval_t maxvalue; /**< TODO: ?? */
    func_meanval_t meanvalue; /**< TODO ?? */
    func_stddval_t standdeviationvalue; /**< TODO: ?? */
    func_reserved4_t reservedlocation4; /**< meh */
    func_reserved5_t reservedlocation5; /**< meh */
    func_hf_source_safe_switch_t hf_source_safe_switch; /**< HF source safe switch */
    func_compain_t selectcompainput; /**< TODO: ?? */
    func_comparef_t selectcomparef; /**< TODO: ?? */
    func_adccompbin_t selectadccompbinput; /**< TODO: ?? */
    func_dacvref_t selectdacvref; /**< TODO: ?? */
} hard_api_t;

/** @ingroup cpu_specific_peripheral_memory_map
  * @{
  */
/**
 * @brief   Start address of the ROM hard API access table (located after the
 *          ROM FW rev field)
 */
#define HARD_API_BASE (0x10000048)
/** @} */

/** 
 * @brief Pointer to the ROM HAPI table
 */
#define HARD_API ((hard_api_t *) HARD_API_BASE)

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif /* CC13X2_ROM_H */

/** @}*/
