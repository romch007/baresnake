#ifndef BARESNAKE_CMOS_H
#define BARESNAKE_CMOS_H

#include <stdint.h>

uint8_t cmos_read_register(uint8_t reg);
uint32_t cmos_read_seconds();

#endif
