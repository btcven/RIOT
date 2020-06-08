/*
 * Copyright (C) 2014 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @addtogroup      cpu_cc26x2_cc13x2
 * @{
 *
 * @file
 * @brief           Linker script for the CC26x2/CC13x2 MCUs
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

INCLUDE cortexm_rom_offset.ld

/* Memory Space Definitions: */
MEMORY
{
    /* rom size is technically near 352K */
    rom      (rx)   : ORIGIN = _rom_start_addr + _rom_offset, LENGTH = _fw_rom_length
    ccfg     (rx)   : ORIGIN = 0x00057FA8,                    LENGTH = 88
    gpram           : ORIGIN = 0x11000000,                    LENGTH = 8K
    ram      (w!rx) : ORIGIN = _ram_start_addr,               LENGTH = _ram_length
}

/* MCU Sepcific Section Definitions */
SECTIONS
{
    .ccfg :
    {
        KEEP(*(.ccfg))
    } > ccfg

    .gpram :
    {
    } > gpram
}

INCLUDE cortexm_base.ld

/* @} */
