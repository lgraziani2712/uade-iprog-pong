#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "./vec.hpp"

class PuntajeJugador {
 public:
  PuntajeJugador(SDL_Renderer* renderer, TTF_Font* fuente, Vec posicion);
  ~PuntajeJugador();

  void Dibujar();
  void Aumentar();

 private:
  int puntaje = 0;
  Vec posicion;
  SDL_Renderer* renderer;
  TTF_Font* fuente;
  SDL_Surface* surface{};
  SDL_Texture* texture{};
  SDL_Rect rect{};
};
