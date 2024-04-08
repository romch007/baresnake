#include "timer.h"

static volatile int ticks = 0;

void wait_ticks(int n) {
  volatile int current_ticks = ticks;

  while (ticks - current_ticks < n)
    ;
}

void tick() {
  ticks++;
}
