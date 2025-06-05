#pragma once

#include <SDL2/SDL_ttf.h>

#include "grid.hpp"
#include "window.hpp"

// std
#include <string>

namespace GOL {
class Game {
  Grid grid;
  Window window;
  int step_number = 0;
  int population = 0;
  int start_population = 0;
  int delay = 100;
  int delay_step = 25;
  bool autoplay_mode = false;
  std::vector<std::pair<int, int>> must_die; // )
  std::vector<std::pair<int, int>> must_born;
  std::vector<std::vector<bool>> start_position = grid.rects;
  void print_welcome_message();
  bool check_event(SDL_Event &event);
  void fill_must_die_and_born_vectors();
  void game_step_forward();
  int count_neighbours(int x, int y); // alive neighbours
public:
  Game(int w_cell = 30, int h_cell = 25);
  void run();
};
} // namespace GOL