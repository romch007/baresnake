#ifndef BARESNAKE_RANDOM_H
#define BARESNAKE_RANDOM_H

static int rseed = 0;

#define RAND_MAX_32 ((1U << 31) - 1)
#define RAND_MAX ((1U << 15) - 1)

static inline void srand(int x) {
  rseed = x;
}

static inline int rand() {
  return (rseed = (rseed * 214013 + 2531011) & RAND_MAX_32) >> 16;
}

static inline int randrange(int max) {
  return rand() % max;
}

#endif
