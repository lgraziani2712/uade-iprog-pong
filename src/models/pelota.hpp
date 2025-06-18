#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <array>
#include "colision.hpp"
#include "vec.hpp"

#define PELOTA_ANCHO 15
#define PELOTA_ALTO 15

class Pelota {
 public:
  Pelota(float x, float y, Mix_Chunk* golpePaleta, Mix_Chunk* golpePared);
  void Dibujar(SDL_Renderer* renderer);
  void Actualizar(float dt);
  std::array<float, 4> Vertices();
  void Colision(Contacto contacto);
  void Reiniciar(float x, float y);
  Contacto ColisionConPared(int windowWidth, int windowHeight);
  Vec Velocidad();

 private:
  float celeridad = 1.0f;
  Vec posicion;
  Vec velocidad;
  SDL_Rect rect{};
  Mix_Chunk *golpePaleta, *golpePared;
};
