#include "red_window.hpp"

void redWindowGameRender(SDL_Window* window, SDL_Renderer* renderer,
                         double deltaTime, SDL_Event& event) {
  // Color de fondo (rojo)
  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderClear(renderer);
}
