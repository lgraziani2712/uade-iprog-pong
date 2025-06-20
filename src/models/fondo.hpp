#pragma once

#include <SDL2/SDL.h>
#include "vec.hpp"

class Fondo {
 public:
  Fondo(SDL_Renderer* renderer, int width, int height);
  ~Fondo();

  void Dibujar();

 private:
  int width, height;
  SDL_Renderer* renderer;
  SDL_Texture* pasto{};
  SDL_Texture* tierra{};
  SDL_Texture* roca{};
  SDL_Rect rect{};
};
