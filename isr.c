#include "isr.h"
#include "idt.h"
#include "port.h"
#include "pic.h"
#include "vga.h"
#include "keyboard.h"
#include "timer.h"

static const char* cpu_exception_name(uint32_t code) {
  switch (code) {
#define BARESNAKE_CPU_EXCEPTION(A, B) \
    case B:                           \
      return #A;
#include "cpu_exceptions.h"
  }

  return NULL;
}

void isr_handler(struct isr_registers regs) {
  const char* error_name = cpu_exception_name(regs.int_no);

  terminal_printf("[ERROR] CPU exception: %s\n", error_name);
}

void irq_handler(struct isr_registers regs) {
  if (regs.int_no == 32) {
    tick();
  }

  if (regs.int_no == 33) {
    keyboard_handle_press();
  }

  if (regs.int_no >= 40) {
    outb(SLAVE_COMMAND, PIC_RESET);
  }

  outb(MASTER_COMMAND, PIC_RESET);
}
