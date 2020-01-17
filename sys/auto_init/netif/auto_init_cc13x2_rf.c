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
 * @brief   Auto initialization for the cc13x2 network interface
 *
 * @author  Aaron Sowry <aaron@mutex.nz>
 */

#ifdef MODULE_CC13X2_RF

#define ENABLE_DEBUG (1)
#include "debug.h"
#include "net/gnrc/netif/ieee802154.h"

#include "cc13x2_rf.h"

/**
 * @brief   Define stack parameters for the MAC layer thread
 * @{
 */
#define CC13X2_MAC_STACKSIZE       (THREAD_STACKSIZE_DEFAULT * 2)
#ifndef CC13X2_MAC_PRIO
#define CC13X2_MAC_PRIO            (GNRC_NETIF_PRIO)
#endif

static cc26xx_cc13xx_rf_t cc13x2_rf_dev;
static char _cc13x2_rf_stack[CC13X2_MAC_STACKSIZE];

void auto_init_cc13x2_rf(void)
{
    DEBUG("[auto_init_netif] initializing cc13x2 radio\n");

    cc13x2_setup(&cc13x2_rf_dev);
    DEBUG("[auto_init_netif] gnrc_netif_ieee802154_create\n");
    gnrc_netif_ieee802154_create(_cc13x2_rf_stack,
                                 CC13X2_MAC_STACKSIZE,
                                 CC13X2_MAC_PRIO, "cc13x2_rf",
                                 (netdev_t *)&cc13x2_rf_dev);
}

#else
typedef int dont_be_pedantic;
#endif /* MODULE_CC13X2_RF */
/** @} */
