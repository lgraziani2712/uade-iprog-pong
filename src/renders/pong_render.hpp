#pragma once

#include <SDL2/SDL.h>
#include "../models/paleta.hpp"
#include "../models/pelota.hpp"

class PongRender {
 public:
  PongRender(SDL_Window* window);
  void Dibujar(SDL_Renderer* renderer, double deltaTime, SDL_Event& event);

 private:
  SDL_Window* window;
  int width, height;

  Pelota pelota;
  Paleta paleta1;
  Paleta paleta2;

  void DibujarRed(SDL_Renderer* renderer);
};
