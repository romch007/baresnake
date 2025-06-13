#include "keyboard.h"
#include "port.h"
#include "isr.h"
#include "vga.h"
#include "game.h"

#include <stdint.h>

void keyboard_handler() {
  terminal_printf("keyboard pressed\n");
}

void keyboard_init() {
#ifdef KERNEL_DEBUG
  uint8_t res;

  outb(0x64, 0xFF);
  res = inb(0x64);
  terminal_printf("[DEBUG] keyboard: got status %x after reset\n", res);

  outb(0x64, 0xAA);
  res = inb(0x60);
  if (res == 0x55) {
    terminal_printf("[DEBUG] keyboard: PS/2 controller test passed\n");
  } else if (res == 0xFC) {
    terminal_printf("[DEBUG] keyboard: PS/2 controller test failed\n");
  } else {
    terminal_printf("[DEBUG] keyboard: PS/2 controller responsed to test with unknown code %x\n", res);
  }

  outb(0x64, 0x20);
  res = inb(0x60);

  terminal_printf("[DEBUG] keyboard: PS/2 config byte: %x\n", res);
#endif
}

static uint8_t keyboard_read_scancode() {
  return inb(0x60);
}

static int has_extended = 0;

void keyboard_handle_press() {
  uint8_t scancode = keyboard_read_scancode();

  if (scancode == 0xE0) {
    has_extended = 1;
    return;
  }

  if (has_extended) {
    switch (scancode) {
      case 0x48:
        change_direction(DIRECTION_UP);
        break;
      case 0x50:
        change_direction(DIRECTION_DOWN);
        break;
      case 0x4D:
        change_direction(DIRECTION_RIGHT);
        break;
      case 0x4B:
        change_direction(DIRECTION_LEFT);
        break;
    }

    has_extended = 0;
  }
}
