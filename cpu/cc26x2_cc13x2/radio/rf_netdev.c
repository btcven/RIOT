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

#include "cc26x2_cc13x2_rf_netdev.h"
#include "cc26x2_cc13x2_rf_internal.h"

/* Reference pointer for the IRQ handler */
static netdev_t *_dev;

void _irq_handler(void)
{
    netdev_trigger_event_isr(_dev);
}

static int _get(netdev_t *netdev, netopt_t opt, void *value, size_t max_len)
{
    cc26x2_cc13x2_rf_t *dev = (cc26x2_cc13x2_rf_t *)netdev;

    if (dev == NULL) {
        return -ENODEV;
    }

    switch (opt) {
        case NETOPT_ADDRESS:
            if (max_len < sizeof(uint16_t)) {
                return -EOVERFLOW;
            }
            else {
                *(uint16_t*)value = 0;
            }
            return sizeof(uint16_t);

        case NETOPT_ADDRESS_LONG:
            if (max_len < sizeof(uint64_t)) {
                return -EOVERFLOW;
            }
            else {
                *(uint64_t*)value = 0;
            }
            return sizeof(uint64_t);

        case NETOPT_AUTOACK:
            return sizeof(netopt_enable_t);

        case NETOPT_CHANNEL:
            if (max_len < sizeof(uint16_t)) {
                return -EOVERFLOW;
            }
            else {
                *((uint16_t *)value) = 0;
            }
            return sizeof(uint16_t);

        case NETOPT_CHANNEL_PAGE:
            if (max_len < sizeof(uint16_t)) {
                return -EOVERFLOW;
            }
            else {
                *((uint16_t *)value) = 0;
            }
            return sizeof(uint16_t);

        case NETOPT_DEVICE_TYPE:
            if (max_len < sizeof(uint16_t)) {
                return -EOVERFLOW;
            }
            else {
                *((uint16_t *)value) = NETDEV_TYPE_IEEE802154;
            }
            return sizeof(uint16_t);

        case NETOPT_IS_CHANNEL_CLR:
            if (max_len < sizeof(netopt_enable_t)) {
                return -EOVERFLOW;
            }
            else {
                *((netopt_enable_t *)value) = NETOPT_DISABLE;
            }
            return sizeof(netopt_enable_t);

        case NETOPT_IS_WIRED:
            return -ENOTSUP;

        case NETOPT_PROMISCUOUSMODE:
            if (max_len < sizeof(netopt_enable_t)) {
                return -EOVERFLOW;
            }
            else {
                *((netopt_enable_t *)value) = NETOPT_ENABLE;
            }
            return sizeof(netopt_enable_t);

        case NETOPT_STATE:
            if (max_len < sizeof(netopt_state_t)) {
                return -EOVERFLOW;
            }
            else {
                *((netopt_state_t *)value) = 0;
            }
            return sizeof(netopt_state_t);

        case NETOPT_TX_POWER:
            if (max_len < sizeof(int16_t)) {
                return -EOVERFLOW;
            }
            else {
                *((uint16_t *)value) = 0;
            }
            return sizeof(uint16_t);

        default:
            break;
    }

    int res;

    if (((res = netdev_ieee802154_get((netdev_ieee802154_t *)netdev, opt, value,
                                      max_len)) >= 0) || (res != -ENOTSUP)) {
        return res;
    }

    return -ENOTSUP;
}

static int _set(netdev_t *netdev, netopt_t opt, const void *value, size_t value_len)
{
    cc26x2_cc13x2_rf_t *dev = (cc26x2_cc13x2_rf_t *)netdev;

    if (dev == NULL) {
        return -ENODEV;
    }

    int res;

    if (((res = netdev_ieee802154_set((netdev_ieee802154_t *)netdev, opt, value,
                                      value_len)) >= 0) || (res != -ENOTSUP)) {
        return res;
    }

    return -ENOTSUP;
}

static int _send(netdev_t *netdev, const iolist_t *iolist)
{
    (void)netdev;
    (void)iolist;

    return -EAGAIN;
}

static int _recv(netdev_t *netdev, void *buf, size_t len, void *info)
{
    (void)netdev;
    (void)buf;
    (void)len;
    (void)info;

    return -EAGAIN;
}

static void _isr(netdev_t *netdev)
{
    netdev->event_callback(netdev, NETDEV_EVENT_RX_COMPLETE);
}

static int _init(netdev_t *netdev)
{
    (void)netdev;
    return 0;
}

const netdev_driver_t cc26x2_cc13x2_rf_driver = {
    .get  = _get,
    .set  = _set,
    .send = _send,
    .recv = _recv,
    .isr  = _isr,
    .init = _init,
};

void cc26x2_cc13x2_rf_setup(cc26x2_cc13x2_rf_t* dev)
{
    netdev_t *netdev = (netdev_t *)dev;
    netdev->driver = &cc26x2_cc13x2_rf_driver;

    cc26x2_cc13x2_rf_init();
}
