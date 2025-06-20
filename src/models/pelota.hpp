#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <array>
#include "colision.hpp"
#include "vec.hpp"

#define PELOTA_ANCHO 20
#define PELOTA_ALTO 20

class Pelota {
 public:
  Pelota(SDL_Renderer* renderer, float x, float y);
  ~Pelota();
  void Dibujar();
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
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  Mix_Chunk* golpe;
  int idContacto = -1;
};
