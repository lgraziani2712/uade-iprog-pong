#pragma once

#include <SDL2/SDL.h>
#include "vec.hpp"

#define PADDLE_SPEED 1.0f
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100

class Paleta {
 public:
  Paleta();
  Paleta(float x, float y);

  void Dibujar(SDL_Renderer* renderer);

 private:
  Vec posicion;
  SDL_Rect rect{};
};
