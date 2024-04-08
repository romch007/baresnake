#ifndef BARESNAKE_IDT_H
#define BARESNAKE_IDT_H

#include <stdint.h>

struct idt_entry {
  uint16_t base_lo;
  uint16_t selector;
  uint8_t zero;
  uint8_t flags;
  uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
  uint16_t limit;
  uint32_t base;
} __attribute__((packed));

void idt_init();

#endif
