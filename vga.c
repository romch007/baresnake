#include "vga.h"
#include "utils.h"

#include <stdarg.h>

static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;

void terminal_init() {
  terminal_row = 0;
  terminal_color = 0;

  terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  terminal_buffer = (uint16_t*)0xB8000;

  terminal_clear_all();
}

void terminal_clear_all() {
  for (size_t y = 0; y < VGA_HEIGHT; y++) {
    for (size_t x = 0; x < VGA_WIDTH; x++) {
      const size_t index = y * VGA_WIDTH + x;
      terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
  }
}

void terminal_setcolor(uint8_t color) {
  terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
  const size_t index = y * VGA_WIDTH + x;
  terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
  if (c == '\n') {
    terminal_row++;
    terminal_column = 0;

    if (terminal_row >= VGA_HEIGHT) {
      terminal_clear_all();
      terminal_row = 0;
    }
  } else {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

    if (++terminal_column >= VGA_WIDTH) {
      terminal_column = 0;

      if (++terminal_row >= VGA_HEIGHT) {
        terminal_clear_all();
        terminal_row = 0;
      }
    }
  }
}

void terminal_set_pos(size_t x, size_t y) {
  terminal_column = x;
  terminal_row = y;
}

void terminal_write(const char* data, size_t size) {
  for (size_t i = 0; i < size; i++)
    terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
  terminal_write(data, strlen(data));
}

void terminal_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  size_t format_len = strlen(format);

  for (size_t i = 0; i < format_len; i++) {
    if (format[i] != '%') {
      terminal_putchar(format[i]);
      continue;
    }

    switch (format[i + 1]) {
      case '%':
        terminal_putchar('%');
        break;

      case 's': {
        char* str = va_arg(args, char*);
        terminal_writestring(str);
        break;
      }
      case 'c': {
        int c = va_arg(args, int);
        terminal_putchar(c);
        break;
      }
      case 'd': {
        int d = va_arg(args, int);

        char buf[1024];
        itoa(d, buf, sizeof(buf), 10);

        terminal_writestring(buf);
        break;
      }
      case 'x': {
        int d = va_arg(args, int);

        char buf[1024];
        itoa(d, buf, sizeof(buf), 16);

        terminal_writestring(buf);
        break;
      }
    }

    i++;
  }

  va_end(args);
}

