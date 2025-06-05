#include "paleta.hpp"

Paleta::Paleta() : posicion(Vec(50.0f, PADDLE_HEIGHT)) {}

Paleta::Paleta(float x, float y) : posicion(Vec(x, y - PADDLE_HEIGHT / 2.0f)) {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);
  rect.w = PADDLE_WIDTH;
  rect.h = PADDLE_HEIGHT;
}

void Paleta::Dibujar(SDL_Renderer* renderer) {
  rect.y = static_cast<int>(posicion.y);

  SDL_RenderFillRect(renderer, &rect);
}
