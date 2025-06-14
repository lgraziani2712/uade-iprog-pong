#pragma once

#include <SDL2/SDL.h>
#include <array>
#include "vec.hpp"

#define PELOTA_ANCHO 15
#define PELOTA_ALTO 15

class Pelota {
 public:
  Pelota(float x, float y);
  void Dibujar(SDL_Renderer* renderer);
  // void AplicarVelocidad(bool arriba, bool abajo);
  void Actualizar(float dt);
  std::array<float, 4> Vertices();
  void Rebotar();
  void Colision(int id);

 private:
  float celeridad = 1.0f;
  int colisionId = 0;
  int preColisionId = 0;
  Vec posicion;
  Vec velocidad;
  SDL_Rect rect{};
};
