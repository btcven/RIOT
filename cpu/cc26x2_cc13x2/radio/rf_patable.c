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
 * @brief           CC26x2/CC13x2 IEEE 802.15.4 netdev driver
 *
 * @author          Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#include "cc26x2_cc13x2_rf.h"

cc26x2_cc13x2_rf_pa_t cc26x2_cc13x2_rf_patable[] =
{
#if CONFIG_CC26X2_CC13X2_FORCE_VDDR_HH
    { .dbm = 14, .val = CC26X2_CC13X2_RF_PA_ENTRY(63, 0, 1, 0) },
#endif
    /* 12.5 rounded to 13 */
    { .dbm = 13, .val = CC26X2_CC13X2_RF_PA_ENTRY(36, 0, 0, 89) },
    { .dbm = 12, .val = CC26X2_CC13X2_RF_PA_ENTRY(16, 0, 0, 82) },
    { .dbm = 11, .val = CC26X2_CC13X2_RF_PA_ENTRY(26, 2, 0, 51) },
    { .dbm = 10, .val = CC26X2_CC13X2_RF_PA_ENTRY(18, 2, 0, 31) },
    { .dbm = 9, .val = CC26X2_CC13X2_RF_PA_ENTRY(28, 3, 0, 31) },
    { .dbm = 8, .val = CC26X2_CC13X2_RF_PA_ENTRY(24, 3, 0, 22) },
    { .dbm = 7, .val = CC26X2_CC13X2_RF_PA_ENTRY(20, 3, 0, 19) },
    { .dbm = 6, .val = CC26X2_CC13X2_RF_PA_ENTRY(17, 3, 0, 16) },
    { .dbm = 5, .val = CC26X2_CC13X2_RF_PA_ENTRY(14, 3, 0, 14) },
    { .dbm = 4, .val = CC26X2_CC13X2_RF_PA_ENTRY(13, 3, 0, 11) },
    { .dbm = 3, .val = CC26X2_CC13X2_RF_PA_ENTRY(11, 3, 0, 10) },
    { .dbm = 2, .val = CC26X2_CC13X2_RF_PA_ENTRY(10, 3, 0, 9) },
    { .dbm = 1, .val = CC26X2_CC13X2_RF_PA_ENTRY(9, 3, 0, 9) },
    { .dbm = 0, .val = CC26X2_CC13X2_RF_PA_ENTRY(8, 3, 0, 8) },
    { .dbm = -5, .val = CC26X2_CC13X2_RF_PA_ENTRY(4, 3, 0, 5) },
    { .dbm = -10, .val = CC26X2_CC13X2_RF_PA_ENTRY(2, 3, 0, 5) },
    { .dbm = -15, .val = CC26X2_CC13X2_RF_PA_ENTRY(1, 3, 0, 3) },
    { .dbm = -20, .val = CC26X2_CC13X2_RF_PA_ENTRY(0, 3, 0, 2) },
    { .dbm = 0xff, .val = 0xff }
};
