#include "paleta.hpp"

Paleta::Paleta(float x, float y)
    : posicion(Vec(x, y - PADDLE_HEIGHT / 2.0f)), velocidad(Vec(0.0f, 0.0f)) {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);
  rect.w = PADDLE_WIDTH;
  rect.h = PADDLE_HEIGHT;
}

void Paleta::Dibujar(SDL_Renderer* renderer) {
  rect.y = static_cast<int>(posicion.y);

  SDL_RenderFillRect(renderer, &rect);
}

void Paleta::AplicarVelocidad(bool arriba, bool abajo) {
  if (arriba) {
    velocidad.y = -PADDLE_SPEED;
  } else if (abajo) {
    velocidad.y = PADDLE_SPEED;
  } else {
    velocidad.y = 0.0f;
  }
}

void Paleta::Actualizar(float dt, int height) {
  posicion += velocidad * dt;

  if (posicion.y < 0) {
    // Limite al borde superior
    posicion.y = 0;
  } else if (posicion.y > (height - PADDLE_HEIGHT)) {
    // Limita al borde inferior
    posicion.y = height - PADDLE_HEIGHT;
  }
}
