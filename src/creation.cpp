#include "creation.hpp"
#include <iostream>
#include <stdexcept>
#include "configs.hpp"

SDL_Window* createWindow() {
  SDL_Window* window = SDL_CreateWindow(
      "Pong lgraziani", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      APP_WINDOW_WIDTH, APP_WINDOW_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);

  if (window == NULL) {
    throw std::runtime_error(SDL_GetError());
  }

  return window;
}

SDL_Renderer* createRenderer(SDL_Window* window) {
  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (renderer == NULL) {
    throw std::runtime_error(SDL_GetError());
  }

  return renderer;
}
