#include "window.hpp"

// std
#include <iostream>
#include <stdexcept>

namespace GOL {
Window::Window(int w, int h, std::string title, int x, int y, Uint32 flags)
    : width(w), height(h), x(x), y(y), title(title), flags(flags) {
  SDL_CreateWindowAndRenderer(width, height, flags, &window, &renderer);
  if (window == nullptr)
    throw std::runtime_error("Failed to create a window\n" +
                             std::string(SDL_GetError()));
  if (renderer == nullptr)
    throw std::runtime_error("Failed to create a renderer\n" +
                             std::string(SDL_GetError()));
}

Window::~Window() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
}

void Window::draw_rect(const SDL_Rect &rect, const SDL_Color &color) {
  if (should_clear)
    window_clear();
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(renderer, &rect);
  SDL_SetRenderDrawColor(renderer, 33, 33, 33, 33);
  SDL_RenderDrawRect(renderer, &rect);
}
void Window::window_update() {
  SDL_RenderPresent(renderer);
  should_clear = true;
}

} // namespace GOL