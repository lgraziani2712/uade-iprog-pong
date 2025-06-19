#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "vec.hpp"

enum Alineacion { Izq, Dcha, Centro };

class Texto {
 public:
  Texto(SDL_Renderer* renderer, TTF_Font* fuente, const char* texto,
        Alineacion alineacion, Vec posicion);
  ~Texto();

  void Actualizar(const char* texto);
  void Dibujar();

 private:
  Vec posicion;
  SDL_Renderer* renderer;
  TTF_Font* fuente;
  SDL_Surface* surface{};
  SDL_Texture* texture{};
  SDL_Rect rect{};
  Alineacion alineacion;
};
