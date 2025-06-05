#pragma once

#include <SDL2/SDL.h>

// std
#include <string>

namespace GOL {
class Window {
  int width, height, x, y, flags;
  std::string title;
  SDL_Window *window;
  SDL_Renderer *renderer;
  bool should_clear = true;
  void window_clear() {
    SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                           background_color.b, background_color.a);
    SDL_RenderClear(renderer);
    should_clear = false;
  }

public:
  SDL_Color background_color{.r = 255, .g = 255, .b = 255, .a = 255};

  Window(int w, int h, std::string title = "window",
         int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED,
         Uint32 flags = 0);
  Window(Window &) = delete;
  Window(Window &&) = delete;
  Window &operator=(Window &) = delete;
  Window &operator=(Window &&) = delete;
  ~Window();

  SDL_Window *get_window() const noexcept { return window; }
  SDL_Renderer *get_renderer() const noexcept { return renderer; }
  void draw_rect(const SDL_Rect &rect, const SDL_Color &color);
  void window_update();
};
} // namespace GOL