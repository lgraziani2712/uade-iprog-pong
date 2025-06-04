#include <SDL2/SDL.h>

#include "red_window.hpp"

void redWindowGame(SDL_Renderer* renderer) {
  // Color de fondo (rojo)
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);
}
