#include "game.h"
#include "vga.h"
#include "random.h"
#include "utils.h"

#define SNAKE_BODY_CHAR '#'
#define APPLE_CHAR '@'

#define SNAKE_BODY_COLOR vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK)
#define APPLE_COLOR vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK)

#define MIDDLE_X (VGA_WIDTH / 2)
#define MIDDLE_Y (VGA_HEIGHT / 2)

struct point {
  int x;
  int y;
};

struct point snake_body[VGA_WIDTH * VGA_HEIGHT];
int snake_body_len;

struct point apple;
struct point last_pos;

enum direction direction;
int score;

const char* death_message = "You died!";

static void grow_snake() {
  snake_body[snake_body_len] = last_pos;

  snake_body_len++;
}

static int check_death() {
  struct point head = snake_body[0];

  if ((head.x < 0 || head.x >= VGA_WIDTH) || (head.y < 0 || head.y >= VGA_HEIGHT))
    return 1;

  for (int i = 1; i < snake_body_len; i++)
    if (snake_body[i].x == head.x && snake_body[i].y == head.y)
      return 1;

  return 0;
}

void draw_game() {
  terminal_clear_all();
  terminal_set_pos(0, 0);
  terminal_printf("Score: %d", score);

  // draw apple
  terminal_putentryat(APPLE_CHAR, APPLE_COLOR, apple.x, apple.y);

  // draw snake body
  for (int i = 0; i < snake_body_len; i++)
    terminal_putentryat(SNAKE_BODY_CHAR, SNAKE_BODY_COLOR, snake_body[i].x, snake_body[i].y);
}

void draw_death_screen() {
  terminal_clear_all();
  terminal_set_pos(MIDDLE_X - ((strlen(death_message) - 1) / 2), MIDDLE_Y);
  terminal_write(death_message, strlen(death_message));
}

int update_game() {
  if (check_death())
    return 0;

  last_pos = snake_body[snake_body_len - 1];

  for (int i = snake_body_len - 1; i >= 1; i--) {
    snake_body[i] = snake_body[i - 1];
  }

  switch (direction) {
    case DIRECTION_UP:
      snake_body[0].y -= 1;
      break;
    case DIRECTION_DOWN:
      snake_body[0].y += 1;
      break;
    case DIRECTION_LEFT:
      snake_body[0].x -= 1;
      break;
    case DIRECTION_RIGHT:
      snake_body[0].x += 1;
      break;
  }

  if (snake_body[0].x == apple.x && snake_body[0].y == apple.y) {
    score++;
    grow_snake();

    apple.x = randrange(VGA_WIDTH);
    apple.y = randrange(VGA_HEIGHT);
  }

  return 1;
}

void start_game() {
  direction = DIRECTION_DOWN;
  score = 0;

  snake_body[0].x = MIDDLE_X;
  snake_body[0].y = MIDDLE_Y;
  snake_body_len = 1;

  apple.x = randrange(VGA_WIDTH);
  apple.y = randrange(VGA_HEIGHT);

  terminal_clear_all();
}

void change_direction(enum direction dir) {
  if ((direction == DIRECTION_UP && dir == DIRECTION_DOWN)
   || (direction == DIRECTION_DOWN && dir == DIRECTION_UP)
   || (direction == DIRECTION_LEFT && dir == DIRECTION_RIGHT)
   || (direction == DIRECTION_RIGHT && dir == DIRECTION_LEFT)
  ) {
    return;
  }

  direction = dir;
}
