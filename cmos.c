#include "cmos.h"
#include "port.h"

uint8_t cmos_read_register(uint8_t reg) {
  outb(0x70, (1 << 7) | reg);
  return inb(0x71);
}

uint32_t cmos_read_seconds() {
  uint8_t seconds = cmos_read_register(0x00);
  uint8_t minutes = cmos_read_register(0x02);
  uint8_t hours = cmos_read_register(0x04);

  return seconds + (minutes * 60) + (hours * 3600);
}
