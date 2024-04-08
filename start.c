#include "keyboard.h"
#include "vga.h"
#include "gdt.h"
#include "idt.h"
#include "pic.h"
#include "game.h"
#include "timer.h"
#include "random.h"
#include "cmos.h"

void kmain(void) {
  gdt_init();
  idt_init();
  terminal_init();

  terminal_printf("----------------------------\n");
  terminal_printf("baresnake by Romain Chardiny\n");
  terminal_printf("----------------------------\n");

  remap_pic();
  keyboard_init();

  srand(cmos_read_seconds());

  start_game();

  while (update_game()) {
    draw_game();
    wait_ticks(2);
  }

  draw_death_screen();
}
