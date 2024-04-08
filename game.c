#include "game.h"
#include "vga.h"
#include "random.h"

#define MAX_BODY_LEN 20

#define SNAKE_BODY_CHAR '#'
#define APPLE_CHAR '@'

#define SNAKE_BODY_COLOR vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK)
#define APPLE_COLOR vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK)

struct point {
  size_t x;
  size_t y;
};

struct game_state {
  struct point snake_body[MAX_BODY_LEN];
  size_t snake_body_len;
  struct point apple;
  enum direction direction;
  int score;

  struct point last_pos;
  int is_dead;
};

struct game_state game;

static void grow_snake() {
  game.snake_body[game.snake_body_len].x = game.last_pos.x;
  game.snake_body[game.snake_body_len].y = game.last_pos.y;

  game.snake_body_len++;
}

static void check_death() {
  struct point head = game.snake_body[0];

  if ((0 < head.x || head.x >= VGA_WIDTH) || (0 < head.y || head.y >= VGA_HEIGHT))
    game.is_dead = 1;

  for (size_t i = 1; i < game.snake_body_len; i++)
    if (game.snake_body[i].x == head.x && game.snake_body[i].y == head.y)
      game.is_dead = 1;
}

void draw_game() {
  terminal_clear_all();

  // draw apple
  terminal_putentryat(APPLE_CHAR, APPLE_COLOR, game.apple.x, game.apple.y);

  // draw snake body
  for (size_t i = 0; i < game.snake_body_len; i++)
    terminal_putentryat(SNAKE_BODY_CHAR, SNAKE_BODY_COLOR, game.snake_body[i].x, game.snake_body[i].y);
}

void update_game() {
  check_death();

  game.last_pos.x = game.snake_body[game.snake_body_len - 1].x;
  game.last_pos.y = game.snake_body[game.snake_body_len - 1].y;

  for (size_t i = game.snake_body_len - 1; i >= 1; i--) {
    game.snake_body[i].x = game.snake_body[i - 1].x;
    game.snake_body[i].y = game.snake_body[i - 1].y;
  }

  switch (game.direction) {
    case DIRECTION_UP:
      game.snake_body[0].y -= 1;
      break;
    case DIRECTION_DOWN:
      game.snake_body[0].y += 1;
      break;
    case DIRECTION_LEFT:
      game.snake_body[0].x -= 1;
      break;
    case DIRECTION_RIGHT:
      game.snake_body[0].x += 1;
      break;
  }

  if (game.snake_body[0].x == game.apple.x && game.snake_body[0].y == game.apple.y) {
    game.score++;
    grow_snake();

    game.apple.x = randrange(VGA_WIDTH);
    game.apple.y = randrange(VGA_HEIGHT);
  }
}

void start_game() {
  game.direction = DIRECTION_DOWN;
  game.score = 0;
  game.is_dead = 0;

  size_t middle_x = VGA_WIDTH / 2;
  size_t middle_y = VGA_HEIGHT / 2;

  game.snake_body[0].x = middle_x;
  game.snake_body[0].y = middle_y;
  game.snake_body_len = 1;

  game.apple.x = randrange(VGA_WIDTH);
  game.apple.y = randrange(VGA_HEIGHT);

  terminal_clear_all();
}

void change_direction(enum direction dir) {
  game.direction = dir;
}
