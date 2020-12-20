/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_cc26xx_cc13xx
 * @ingroup     drivers_periph_flashpage
 * @{
 *
 * @file
 * @brief       Low-level flash page driver implementation
 *
 * @author      Jean Pierre Dudey <jeandudey@hotmail.com>
 *
 * @}
 */

#include "cpu.h"
#include "periph/flashpage.h"

#include "mutex.h"

#define ENABLE_DEBUG 1
#include "debug.h"

#define MAX_WRITE_SIZE (8U) /**< number of bytes to write at a time, it's
                                 small to minimize latency */

static mutex_t _lock = MUTEX_INIT;

static uint32_t _flash_cache_disable(void)
{
    uint32_t mode = VIMS->STAT & VIMS_STAT_MODE_m;

    /* disable linebuffers */
    VIMS->CTL |= (VIMS_CTL_IDCODE_LB_DIS | VIMS_CTL_SYSBUS_LB_DIS);

    /* if not on GPRAM, the VIMS cache is enabled */
    if (mode != VIMS_STAT_MODE_GPRAM) {
        /* Set VIMS to GPRAM mode */
        reg32_t tmp = VIMS->CTL;
        tmp &= ~VIMS_CTL_MODE_m;
        tmp |= VIMS_CTL_MODE_GPRAM;
        VIMS->CTL = tmp;

        /* wait for the mode change to be done */
        while ((VIMS->STAT & VIMS_STAT_MODE_m) != VIMS_STAT_MODE_GPRAM) {}
    }

    return mode;
}

static void _flash_cache_restore(uint32_t mode)
{
    if (mode != VIMS_STAT_MODE_GPRAM) {
        /* enable VIMS again */
        VIMS->CTL |= VIMS_CTL_MODE_CACHE;
    }

    /* enable linebuffers */
    VIMS->CTL &= ~(VIMS_CTL_IDCODE_LB_DIS | VIMS_CTL_SYSBUS_LB_DIS);
}

static inline uint32_t _flash_sector_size(void)
{
    /* get sector size in kibibytes (KiB) and convert to bytes */
    uint32_t size = ((FLASH->FCFG_B0_SSIZE0
                  &  FLASH_FCFG_B0_SSIZE0_B0_SECT_SIZE_m)
                 >> FLASH_FCFG_B0_SSIZE0_B0_SECT_SIZE_s) * 1024;
    DEBUG("[flashpage]: flash sector size=%"PRIu32"\n", size);
    return size;
}

static inline uint32_t _flash_size(void)
{
    uint32_t size = ((FLASH->FLASH_SIZE
                  &  FLASH_FLASH_SIZE_SECTORS_m)
                 >> FLASH_FLASH_SIZE_SECTORS_s) * _flash_sector_size();
    DEBUG("[flashpage]: flash size=%"PRIu32"\n", size);
    return size;
}

static uint32_t _flash_sector_erase(uint32_t sector_addr)
{
    /* sanity check the sector address */
    assert(sector_addr <= (FLASH_BASE + _flash_size() - _flash_sector_size()));
    assert((sector_addr & (_flash_sector_size() - 1)) == 0);

    /* call ROM function that handles the actual erase operation */
    uint32_t ret = rom_flash_sector_erase(sector_addr);
    /* enable standby in flash bank since ROM function might have disabled
     * it */
    FLASH->CFG &= ~FLASH_CFG_DIS_STANDBY;

    return ret;
}

static uint32_t _flash_program(const uint8_t *data, uint32_t addr, uint32_t size)
{
    assert((addr + size) <= (FLASH_BASE + _flash_size()));

    /* call ROM function that handles the actual program operation */
    uint32_t ret = rom_flash_program(data, addr, size);
    /* enable standby in flash bank since ROM function might have disabled it */
    FLASH->CFG &= ~FLASH_CFG_DIS_STANDBY;

    return ret;

}

static inline void _erase(uint32_t *page_addr)
{
    const uint32_t sector_size = _flash_sector_size();
    DEBUG("[flashpage] erase: page_addr=%p\n", page_addr);

    uint32_t sector_offset = (uint32_t)page_addr;
    uint32_t size = FLASHPAGE_SIZE;

    uint32_t mode = _flash_cache_disable();
    while (size > 0) {
        unsigned key = irq_disable();
        uint32_t ret = _flash_sector_erase(sector_offset);
        irq_restore(key);

        if (ret != FAPI_STATUS_SUCCESS) {
            DEBUG("[flashpage] erase: failed to write at sector=%"PRIu32"\n",
                  sector_offset);
            assert(0);
        }

        sector_offset += sector_size;
        size -= sector_size;
    }
    _flash_cache_restore(mode);
}

void flashpage_erase(unsigned page)
{
    assert(page < FLASHPAGE_NUMOF);

    uint32_t *page_addr = (uint32_t *)flashpage_addr(page);

    mutex_lock(&_lock);
    _erase(page_addr);
    mutex_unlock(&_lock);
}

static inline void _write(uint32_t address, const uint8_t *data, size_t size)
{
    DEBUG("[flashpage] write: address=%"PRIu32"\n", address);

    uint32_t mode = _flash_cache_disable();
    while (size) {
        uint32_t write_size;
        if (size > MAX_WRITE_SIZE) {
            write_size = MAX_WRITE_SIZE;
        }
        else {
            write_size = size;
        }

        unsigned key = irq_disable();
        uint32_t ret = _flash_program(data, address, write_size);
        irq_restore(key);

        if (ret != FAPI_STATUS_SUCCESS) {
            DEBUG("[flashpage] write: failed to program flash: ret=%"PRIu32"\n",
                  ret);
            assert(0);
        }

        address += write_size;
        data += write_size;
        size -= write_size;
    }
    _flash_cache_restore(mode);
}

void flashpage_write(void *target_addr, const void *data, size_t len)
{
    (void)data;
    (void)len;

    mutex_lock(&_lock);
    _write((uint32_t)target_addr, data, len);
    mutex_unlock(&_lock);
}
