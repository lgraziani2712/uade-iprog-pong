#pragma once

#include <SDL2/SDL.h>
#include "../models/pelota.hpp"

class PongRender {
 public:
  PongRender(SDL_Window* window);
  void Dibujar(SDL_Renderer* renderer, double deltaTime, SDL_Event& event);

 private:
  SDL_Window* window;
  Pelota pelota;
  int width, height;
  void DibujarRed(SDL_Renderer* renderer);
};
