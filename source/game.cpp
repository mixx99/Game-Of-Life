#include "game.hpp"

// std
#include <cmath>
#include <iostream>

namespace GOL {
Game::Game(int w_cell, int h_cell)
    : grid(w_cell, h_cell),
      window(grid.grid_cell_size * grid.grid_width,
             grid.grid_cell_size * grid.grid_height, "Game Of Life") {}

void Game::run() {
  print_welcome_message();
  SDL_Event event;
  while (true) {
    if (!check_event(event))
      return;

    if (autoplay_mode) {
      game_step_forward();
      SDL_Delay(delay);
    }
    grid.draw(window);
    window.window_update();
  }
}

void Game::game_step_forward() {
  if (step_number == 0) {
    start_position = grid.rects;
    start_population = population;
  }
  fill_must_die_and_born_vectors();
  for (const auto &i : must_born) {
    grid.rects[i.first][i.second] = 1;
  }
  for (const auto &i : must_die) {
    grid.rects[i.first][i.second] = 0;
  }
  population += must_born.size() - must_die.size();
  step_number++;
  std::cout << "Current step: " << step_number
            << " Current population: " << population << '\n';
}

void Game::fill_must_die_and_born_vectors() {
  must_born.clear();
  must_die.clear();
  for (int i = 0; i < grid.rects.size(); ++i) {
    for (int j = 0; j < grid.rects[i].size(); ++j) {
      int neighbourses = count_neighbours(i, j);
      if (grid.rects[i][j] == 0 && neighbourses == 3)
        must_born.push_back(std::make_pair(i, j));
      else if (grid.rects[i][j] == 1 && (neighbourses < 2 || neighbourses > 3))
        must_die.push_back(std::make_pair(i, j));
    }
  }
}

int Game::count_neighbours(int x, int y) {
  int result = 0;
  for (int i = -1; i <= 1; ++i) {
    for (int j = -1; j <= 1; ++j) {
      if (i == 0 && j == 0)
        continue;
      int n = (x + i + grid.grid_width) % grid.grid_width;
      int m = (y + j + grid.grid_height) % grid.grid_height;
      if (grid.rects[n][m])
        result++;
    }
  }
  return result;
}

bool Game::check_event(SDL_Event &event) {
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      return false;
    }
    if (event.type == SDL_MOUSEBUTTONDOWN &&
        grid.rects[event.motion.x / grid.grid_cell_size]
                  [event.motion.y / grid.grid_cell_size] == 0 &&
        step_number == 0) {
      grid.rects[event.motion.x / grid.grid_cell_size]
                [event.motion.y / grid.grid_cell_size] = 1;
      population++;
    } else if (event.type == SDL_MOUSEBUTTONDOWN && step_number == 0) {
      grid.rects[event.motion.x / grid.grid_cell_size]
                [event.motion.y / grid.grid_cell_size] = 0;
      population--;
    }
    if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_n:
        if (!autoplay_mode)
          game_step_forward();
        break;
      case SDLK_s:
        if (autoplay_mode) {
          autoplay_mode = false;
          std::cout << "Autoplay disabled\n";
        } else {
          autoplay_mode = true;
          std::cout << "Autoplay enabled\n";
        }
        break;
      case SDLK_k:
        delay += delay_step;
        std::cout << "Current autoplay delay = " << delay << "ms.\n";
        break;
      case SDLK_j:
        if (delay - delay_step >= 0)
          delay -= delay_step;
        std::cout << "Current autoplay delay = " << delay << "ms\n";
        break;
      case SDLK_r:
        grid.rects = start_position;
        step_number = 0;
        population = start_population;
        std::cout << "Reset position\n";
        break;
      case SDLK_c:
        for(int i = 0; i < grid.rects.size(); ++i)
          for(int j = 0; j < grid.rects[i].size(); ++j)
            grid.rects[i][j] = 0;
        start_population = 0;
        population = 0;
        step_number = 0;
        start_position = grid.rects;
        std::cout << "Cleaned\n";
        break;
      }
    }
  }
  return true;
}
void Game::print_welcome_message() {
  std::cout << R"(Welcome to
   ____                         ___   __   _     _  __      
  / ___| __ _ _ __ ___   ___   / _ \ / _| | |   (_)/ _| ___ 
 | |  _ / _` | '_ ` _ \ / _ \ | | | | |_  | |   | | |_ / _ \
 | |_| | (_| | | | | | |  __/ | |_| |  _| | |___| |  _|  __/
  \____|\__,_|_| |_| |_|\___|  \___/|_|   |_____|_|_|  \___|                                                      
  )" << '\n';
  std::cout << "Settings:\n"
            << "Step forward              - 'n'\n"
            << "Enable/Disable autoplay   - 's'\n"
            << "Reset position            - 'r'\n"
            << "Speed up(autoplay mode)   - 'k'\n"
            << "Speed down(autoplay mode) - 'j'\n"
            << "Clean everything          - 'c'\n"
            << "LMB to fill/clear the cell\n";
  std::cout << "Size of field now: " << grid.grid_width << 'x'
            << grid.grid_height << '\n';
  std::cout << "Current delay(for autoplay mode) - " << delay << "ms.\n";
}

} // namespace GOL