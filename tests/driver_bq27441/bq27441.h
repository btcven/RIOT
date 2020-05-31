#ifndef BQ27441_H
#define BQ27441_H

#include <stdint.h>

uint8_t bq27441_address = 0x55;
/**
 * @brief
 */
enum command
{
    control = 0x00,
    temp = 0x02,
    voltage = 0x04,
    flags = 0x06,
    nom_capacity = 0x08,
    avail_capacity = 0x0A,
    rem_capacity = 0x0C,
    full_capacity = 0x0E,
    avg_current = 0x10,
    stdby_current = 0x12,
    max_current = 0x14,
    avg_power = 0x18,
    soc = 0x1C,
    int_temp = 0x1E,
    soh = 0x20,
    rem_cap_unfl = 0x28,
    rem_cap_fil = 0x2A,
    full_cap_unfl = 0x2C,
    full_cap_fil = 0x2E,
    soc_unfl = 0x30
};

#endif /* BQ27441_H */