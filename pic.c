#include "pic.h"
#include "port.h"

void remap_pic() {
  outb(MASTER_COMMAND, ICW1_INIT | ICW1_ICW4); // Start initialization sequence
  outb(SLAVE_COMMAND, ICW1_INIT | ICW1_ICW4);  // Start initialization sequence
  outb(MASTER_DATA, 0x20);                     // Remap to 0x20
  outb(SLAVE_DATA, 0x28);                      // Remap slave to 0x28
  outb(MASTER_DATA, 4);                        // Tell Master about slave @ IRQ 2
  outb(SLAVE_DATA, 2);                         // Tell slave PIC its cascade ID

  outb(MASTER_DATA, ICW4_8086);
  outb(SLAVE_DATA, ICW4_8086);

  outb(MASTER_DATA, 0x0);
  outb(SLAVE_DATA, 0x0);

  asm volatile("sti");
}
