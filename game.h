#ifndef BARESNAKE_GAME_H
#define BARESNAKE_GAME_H

enum direction {
  DIRECTION_UP,
  DIRECTION_DOWN,
  DIRECTION_LEFT,
  DIRECTION_RIGHT,
};

void start_game();
void draw_game();
void draw_death_screen();
int update_game();
void change_direction(enum direction dir);

#endif
