#pragma once

#include <SDL2/SDL.h>
#include "vec.hpp"

#define BALL_SPEED 1.0f
#define BALL_WIDTH 15
#define BALL_HEIGHT 15

class Pelota {
 public:
  Pelota(float x, float y);
  void Dibujar(SDL_Renderer* renderer);

 private:
  Vec posicion;
  SDL_Rect rect{};
};
