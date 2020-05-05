/*
 * Copyright (C) 2020 Locha Inc
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 *
 */

/*
 * @ingroup sys_auto_init_gnrc_netif
 * @{
 *
 * @file
 * @brief   Auto initialization for the cc26x2/cc13x2 Sub-GHz network interface
 *
 * @author  Jean Pierre Dudey <jeandudey@hotmail.com>
 */

#ifdef MODULE_CC26X2_CC13X2_RF

#include "log.h"
#include "net/gnrc/netif/ieee802154.h"

#include "cc26x2_cc13x2_rf.h"

/**
 * @brief   Define stack parameters for the MAC layer thread
 * @{
 */
#define CC26X2_CC13X2_MAC_STACKSIZE       (THREAD_STACKSIZE_DEFAULT)
#ifndef CC26X2_CC13X2_MAC_PRIO
#define CC26X2_CC13X2_MAC_PRIO            (GNRC_NETIF_PRIO)
#endif

static cc26x2_cc13x2_rf_netdev_t cc26x2_cc13x2_rf_dev;
static char _cc26x2_cc13x2_rf_stack[CC26X2_CC13X2_MAC_STACKSIZE];
static gnrc_netif_t _netif;

void auto_init_cc26x2_cc13x2_rf(void)
{
    LOG_DEBUG("[auto_init_netif] initializing cc26x2_cc13x2 radio\n");

    cc26x2_cc13x2_rf_setup(&cc26x2_cc13x2_rf_dev);
    gnrc_netif_ieee802154_create(&_netif, _cc26x2_cc13x2_rf_stack,
                                 CC26X2_CC13X2_MAC_STACKSIZE,
                                 CC26X2_CC13X2_MAC_PRIO, "cc26x2_cc13x2_rf",
                                 (netdev_t *)&cc26x2_cc13x2_rf_dev);
}

#else
typedef int dont_be_pedantic;
#endif /* MODULE_CC26X2_CC13X2_RF */
/** @} */