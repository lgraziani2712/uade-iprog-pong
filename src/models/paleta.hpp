#pragma once

#include <SDL2/SDL.h>
#include "input.hpp"
#include "pelota.hpp"
#include "vec.hpp"

#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 100

class Paleta {
 public:
  Paleta(int id, float x, float y);

  void Dibujar(SDL_Renderer* renderer);
  void AplicarVelocidad(bool arriba, bool abajo);
  void Actualizar(float dt, int height);
  bool VerificarColision(Pelota* pelota);

 private:
  int id;
  float celeridad = 1.0f;
  Vec posicion;
  Vec velocidad;
  SDL_Rect rect{};
};
