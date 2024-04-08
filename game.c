#include "game.h"
#include "vga.h"
#include "random.h"
#include "utils.h"

#define MAX_BODY_LEN 20

#define SNAKE_BODY_CHAR '#'
#define APPLE_CHAR '@'

#define SNAKE_BODY_COLOR vga_entry_color(VGA_COLOR_GREEN, VGA_COLOR_BLACK)
#define APPLE_COLOR vga_entry_color(VGA_COLOR_RED, VGA_COLOR_BLACK)

struct point {
  int x;
  int y;
};

struct game_state {
  struct point snake_body[MAX_BODY_LEN];
  int snake_body_len;
  struct point apple;
  enum direction direction;
  int score;
  struct point last_pos;
};

struct game_state game;

static void grow_snake() {
  game.snake_body[game.snake_body_len].x = game.last_pos.x;
  game.snake_body[game.snake_body_len].y = game.last_pos.y;

  game.snake_body_len++;
}

static int check_death() {
  struct point head = game.snake_body[0];

  if ((head.x < 0 || head.x >= VGA_WIDTH) || (head.y < 0 || head.y >= VGA_HEIGHT))
    return 1;

  for (int i = 1; i < game.snake_body_len; i++)
    if (game.snake_body[i].x == head.x && game.snake_body[i].y == head.y)
      return 1;

  return 0;
}

void draw_game() {
  terminal_clear_all();
  terminal_set_pos(0, 0);
  terminal_printf("Score: %d", game.score);

  // draw apple
  terminal_putentryat(APPLE_CHAR, APPLE_COLOR, game.apple.x, game.apple.y);

  // draw snake body
  for (int i = 0; i < game.snake_body_len; i++)
    terminal_putentryat(SNAKE_BODY_CHAR, SNAKE_BODY_COLOR, game.snake_body[i].x, game.snake_body[i].y);
}

void draw_death_screen() {
  char message[] = "You died!";

  int middle_x = VGA_WIDTH / 2;
  int middle_y = VGA_HEIGHT / 2;

  terminal_clear_all();
  terminal_set_pos(middle_x - (sizeof(message) / 2), middle_y);
  terminal_write(message, sizeof(message));
}

int update_game() {
  if (check_death())
    return 0;

  game.last_pos.x = game.snake_body[game.snake_body_len - 1].x;
  game.last_pos.y = game.snake_body[game.snake_body_len - 1].y;

  for (int i = game.snake_body_len - 1; i >= 1; i--) {
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

  return 1;
}

void start_game() {
  game.direction = DIRECTION_DOWN;
  game.score = 0;

  int middle_x = VGA_WIDTH / 2;
  int middle_y = VGA_HEIGHT / 2;

  game.snake_body[0].x = middle_x;
  game.snake_body[0].y = middle_y;
  game.snake_body_len = 1;

  game.apple.x = randrange(VGA_WIDTH);
  game.apple.y = randrange(VGA_HEIGHT);

  terminal_clear_all();
}

void change_direction(enum direction dir) {
  if ((game.direction == DIRECTION_UP && dir == DIRECTION_DOWN)
   || (game.direction == DIRECTION_DOWN && dir == DIRECTION_UP)
   || (game.direction == DIRECTION_LEFT && dir == DIRECTION_RIGHT)
   || (game.direction == DIRECTION_RIGHT && dir == DIRECTION_LEFT)
  ) {
    return;
  }

  game.direction = dir;
}
