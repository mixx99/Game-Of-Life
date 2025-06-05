#include "grid.hpp"

namespace GOL {

void Grid::draw(Window &window) {
  SDL_Rect rect{.x = 0, .y = 0, .w = grid_cell_size, .h = grid_cell_size};
  SDL_Color color = grid_color;
  for (int i = 0; i < rects.size(); ++i) {
    for (int j = 0; j < rects[i].size(); ++j) {
      rect.x = i * grid_cell_size;
      rect.y = j * grid_cell_size;
      if (rects[i][j])
        color = grid_filled_color;
      else
        color = grid_color;
      window.draw_rect(rect, color);
    }
  }
}
} // namespace GOL