#include "pelota.hpp"

Pelota::Pelota(float x, float y)
    : posicion(
          // A la posición que recibimos, restamos la mitad del alto y mitad del
          // ancho de la pelota para que ésta esté anclada en su centro
          Vec(x - BALL_WIDTH / 2.0f, y - BALL_HEIGHT / 2.0f)) {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);
  rect.w = BALL_WIDTH;
  rect.h = BALL_HEIGHT;
}

void Pelota::Dibujar(SDL_Renderer* renderer) {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);

  SDL_RenderFillRect(renderer, &rect);
}
