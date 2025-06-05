#include <SDL2/SDL.h>

// std
#include <iostream>
#include <stdexcept>
#include <string>

#include "game.hpp"

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_EVERYTHING);
  try {
    int w = 30, h = 25;
    if (argc == 3) {
      w = std::stoi(argv[1]);
      h = std::stoi(argv[2]);
    }
    GOL::Game game(w, h);
    game.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
  SDL_Quit();
}