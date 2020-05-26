/*
 * Copyright (C) 2018 Anatoliy Atanasov, Iliyan Stoyanov
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     tests
 * @{
 * @file
 * @brief       test aplication for the BQ27441 Lithium Battery fuel gauge by TI
 *
 * @author      Anatoliy Atanasov <anatoliy@6lowpan.io>
 * @author      Iliyan Stoyanov <iliyan@6lowpan.io>
 * @}
 */

#include <stdio.h>
#include "xtimer.h"
#include "bq27441.h"
#include "bq27441_params.h"
#include "periph/gpio.h"

static void _gauge_cb(void *arg)
{
    (void)arg;
    printf("\n BQ27441 CB \n");
}

int main(void)
{
    puts("BQ27441 Lithium Battery Fuel Gauge test application");
    bq27441_t dev;
    dev.cb = _gauge_cb;
    dev.arg = NULL;
    //const unsigned int BATTERY_CAPACITY = 500;

    // gpio_t out_pin = GPIO_PIN(3, 3); // TODO: DEFINE CORRECTLY

    int i2c_acquired = i2c_acquire(params_default[0].bus);

    if (i2c_acquired == -1)
    {
        printf("ERROR - Trying to acquire I2C bus: %d\n", params_default[0].bus);
    }
    else
    {
        printf("OK - Acquired I2C bus: %d\n", params_default[0].bus);

        if (bq27441_init(&dev, params_default))
        {
             printf("OK - Init\n");
            uint16_t device_id = bq27441_get_device_type(&dev); // Read deviceType from BQ27441
            printf("Device id: 0x%02x \n", device_id);
            /*
            uint16_t capacity = bq27441_get_capacity(&dev, REMAIN);
            uint16_t soc = bq27441_get_soc(&dev, FILTERED);
            uint16_t voltage = bq27441_get_voltage(&dev);
            uint16_t current = bq27441_get_current(&dev, AVG);
            uint16_t full_capacity = bq27441_get_capacity(&dev, FULL);
            int16_t power = bq27441_get_power(&dev);
            uint8_t health = bq27441_get_soh(&dev, PERCENT);
            printf("Device id: 0x%02x \n", device_id);
            printf("Capacity : 0x%02x mAh \n", capacity);
            printf("State of charge: 0x%02x %%\n", soc);
            printf("Voltage: 0x%02x mV\n", voltage);
            printf("Current id: 0x%02x mA\n", current);
            printf("Full Capacity: 0x%02x mAh\n", full_capacity);
            printf("Power: 0x%02x mW\n", power);
            printf("Health: 0x%02x %% \n", health);
            */
        }
        else
        {
            printf("ERROR\n");
            i2c_release(params_default[0].bus);
        }

        return 0;
    }
}
