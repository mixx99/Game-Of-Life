#pragma once

#include "window.hpp"
#include <SDL2/SDL.h>
// std
#include <utility>
#include <vector>

namespace GOL {
struct Grid {
  int grid_cell_size = 36;
  int grid_width;
  int grid_height;
  SDL_Color grid_color = {.r = 22, .g = 22, .b = 22, .a = 255};
  SDL_Color grid_filled_color = {.r = 200, .g = 200, .b = 200, .a = 255};
  std::vector<std::vector<bool>> rects;
  void draw(Window &window);

  Grid(int w = 30, int h = 25)
      : grid_width(w), grid_height(h),
        rects(grid_width, std::vector<bool>(grid_height)) {}
};
} // namespace GOL