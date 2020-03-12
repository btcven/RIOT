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
 * @brief           CC26x2, CC13x2 RF driver
 */

#ifndef CC26X2_CC13X2_RF_IEEE802154_H
#define CC26X2_CC13X2_RF_IEEE802154_H

#define RF_IEEE802154_PHR_NUM_BYTES (2) /**< Size of the PHR field in bytes */
#define RF_IEEE802154_UNCODED_SFD_0 (0) /**< Sync word - Start-of-Frame value */

/**
 * @brief   IEEE 802.15.4g frequency band identifiers
 *
 * @see IEEE Std 802.15.4g-2012, Table 68f - SUN PHY frequency band definitions
 *
 * @{
 */
#define RF_IEEE802154_FREQ_BAND_470 (2) /* 470–510 (China) - 470 MHz */
#define RF_IEEE802154_FREQ_BAND_780 (3) /* 779–787 (China) - 780 MHz */
#define RF_IEEE802154_FREQ_BAND_863 (4) /* 863–870 (Europe) - 863 MHz */
#define RF_IEEE802154_FREQ_BAND_896 (5) /* 896–901 (US FCC Part 90) - 896 MHz */
#define RF_IEEE802154_FREQ_BAND_901 (6) /* 901–902 (US FCC Part 24) - 901 MHz */
#define RF_IEEE802154_FREQ_BAND_915 (7) /* 902–928 (US) - 915 MHz */
#define RF_IEEE802154_FREQ_BAND_917 (8) /* 917–923.5 (Korea) - 917 MHz */
#define RF_IEEE802154_FREQ_BAND_920 (9) /* 920–928 (Japan) - 920 MHz */
#define RF_IEEE802154_FREQ_BAND_950 (11) /* 950–958 (Japan) - 950 MHz */
/** @} */

/**
 * @brief   Default band selection to band 7 - 915 MHz
 */
#ifndef RF_IEEE802154_FREQ_BAND_ID
#define RF_IEEE802154_FREQ_BAND_ID RF_IEEE802154_FREQ_BAND_915
#endif

#if (RF_IEEE802154_FREQ_BAND_ID == RF_IEEE802154_FREQ_BAND_470)
#define RF_IEEE802154_CHAN_MIN     (0)
#define RF_IEEE802154_CHAN_MAX     (198)
#define RF_IEEE802154_FREQ_SPACING (200)
#define RF_IEEE802154_CHAN0_FREQ   (470200)

#define RF_PROP_MODE_CENTER_FREQ   (0x01EA)
#define RF_PROP_MODE_LO_DIVIDER    (0x0A)

#elif (RF_IEEE802154_FREQ_BAND_ID == RF_IEEE802154_FREQ_BAND_780)
#define RF_IEEE802154_CHAN_MIN     (0)
#define RF_IEEE802154_CHAN_MAX     (38)
#define RF_IEEE802154_FREQ_SPACING (200)
#define RF_IEEE802154_CHAN0_FREQ   (779200)

#define RF_PROP_MODE_CENTER_FREQ   (0x030F)
#define RF_PROP_MODE_LO_DIVIDER    (0x06)

#elif (RF_IEEE802154_FREQ_BAND_ID == RF_IEEE802154_FREQ_BAND_863)
#define RF_IEEE802154_CHAN_MIN     (0)
#define RF_IEEE802154_CHAN_MAX     (33)
#define RF_IEEE802154_FREQ_SPACING (200)
#define RF_IEEE802154_CHAN0_FREQ   (863125)

#define RF_PROP_MODE_CENTER_FREQ   (0x0362)
#define RF_PROP_MODE_LO_DIVIDER    (0x05)

#elif (RF_IEEE802154_FREQ_BAND_ID == RF_IEEE802154_FREQ_BAND_915)
#define RF_IEEE802154_CHAN_MIN     (0)
#define RF_IEEE802154_CHAN_MAX     (128)
#define RF_IEEE802154_FREQ_SPACING (200)
#define RF_IEEE802154_CHAN0_FREQ   (902200)

#define RF_PROP_MODE_CENTER_FREQ   (0x0393)
#define RF_PROP_MODE_LO_DIVIDER    (0x05)

#elif (RF_IEEE802154_FREQ_BAND_ID == RF_IEEE802154_FREQ_BAND_920)
#define RF_IEEE802154_CHAN_MIN     (0)
#define RF_IEEE802154_CHAN_MAX     (37)
#define RF_IEEE802154_FREQ_SPACING (200)
#define RF_IEEE802154_CHAN0_FREQ   (920600)

#define RF_PROP_MODE_CENTER_FREQ   (0x039C)
#define RF_PROP_MODE_LO_DIVIDER    (0x05)

#elif (RF_IEEE802154_FREQ_BAND_ID == RF_IEEE802154_FREQ_BAND_950)
#define RF_IEEE802154_CHAN_MIN     (0)
#define RF_IEEE802154_CHAN_MAX     (32)
#define RF_IEEE802154_FREQ_SPACING (200)
#define RF_IEEE802154_CHAN0_FREQ   (951000)

#define RF_PROP_MODE_CENTER_FREQ   (0x03BA)
#define RF_PROP_MODE_LO_DIVIDER    (0x05)

#else
#error "The selected IEEE 802.15.4g frequency band is not supported"
#endif

#define RF_IEEE802154_MAX_FRAME_LEN (2047) /**< Maximum frame length */
#define RF_IEEE802154_LEN_OFFSET (0xFC) /**< Length offset */

#endif /* CC26X2_CC13X2_RF_IEEE802154_H */
