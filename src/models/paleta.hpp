#pragma once

#include <SDL2/SDL.h>
#include "colision.hpp"
#include "input.hpp"
#include "pelota.hpp"
#include "vec.hpp"

#define PALETA_ANCHO 30
#define PALETA_ALTO 120

class Paleta {
 public:
  Paleta(SDL_Renderer* renderer, float x, float y);
  ~Paleta();

  void Dibujar();
  void AplicarVelocidad(bool arriba, bool abajo);
  void Actualizar(float dt, int height);
  void Colision(Pelota* pelota);
  void Reiniciar(float x, float y);

 private:
  float celeridad = 1.0f;
  Vec posicion;
  Vec velocidad;
  SDL_Rect rect{};
  SDL_Renderer* renderer;
  SDL_Texture* texture;
};
