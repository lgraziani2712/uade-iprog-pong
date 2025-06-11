#pragma once

#include <SDL2/SDL.h>
#include "input.hpp"
#include "vec.hpp"

#define PADDLE_SPEED 750.0f
#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100

class Paleta {
 public:
  Paleta(float x, float y);

  void Dibujar(SDL_Renderer* renderer);
  void AplicarVelocidad(bool arriba, bool abajo);
  void Actualizar(float dt, int height);

 private:
  Vec posicion;
  Vec velocidad;
  SDL_Rect rect{};
};
