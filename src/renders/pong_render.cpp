#include <SDL2/SDL.h>

#include "pong_render.hpp"

PongRender::PongRender(SDL_Window* window) : window(window) {
  SDL_GetWindowSize(window, &width, &height);

  pelota = Pelota(width / 2.0f, height / 2.0f);
  paleta1 = Paleta(50.0f, height / 2.0f);
  paleta2 = Paleta(width - 50.0f, height / 2.0f);
}

void PongRender::Dibujar(SDL_Renderer* renderer, double deltaTime,
                         SDL_Event& event) {
  // Limpia la pantalla en negro
  SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
  SDL_RenderClear(renderer);
  // Actualizo el width y height
  SDL_GetWindowSize(window, &width, &height);

  // Dibujo los objetos
  DibujarRed(renderer);
  pelota.Dibujar(renderer);
  paleta1.Dibujar(renderer);
  paleta2.Dibujar(renderer);
}

void PongRender::DibujarRed(SDL_Renderer* renderer) {
  // Dice a SDL que setee el render con color blanco
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  // Dibuja la red. Mejora implementación del tuto. Itera menos veces.
  for (int y = 0; y < height; y += 5) {
    // Dibuja líneas de [0,3], [5,8]. Siempre con un píxel vacío.
    SDL_RenderDrawLine(renderer, width / 2, y, width / 2, y + 3);
  }
}
