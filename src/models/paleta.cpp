#include "paleta.hpp"
#include <iostream>

Paleta::Paleta(int id, float x, float y)
    : posicion(Vec(x, y - PADDLE_HEIGHT / 2.0f)),
      velocidad(Vec(0.0f, 0.0f)),
      id(id) {
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
    velocidad.y = -celeridad;
  } else if (abajo) {
    velocidad.y = celeridad;
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

bool Paleta::VerificarColision(Pelota* pelota) {
  auto verticesPelota = pelota->Vertices();
  float vertices[4] = {posicion.x, posicion.x + PADDLE_WIDTH, posicion.y,
                       posicion.y + PADDLE_HEIGHT};

  if (verticesPelota[0] >= vertices[1]) {
    return false;
  }
  if (verticesPelota[1] <= vertices[0]) {
    return false;
  }
  if (verticesPelota[2] >= vertices[3]) {
    return false;
  }
  if (verticesPelota[3] <= vertices[2]) {
    return false;
  }

  pelota->Colision(id);

  return true;
}
