#include "pelota.hpp"

Pelota::Pelota(float x, float y)
    // A la posición que recibimos, restamos la mitad del alto y mitad del
    // ancho de la pelota para que ésta esté anclada en su centro
    : posicion(Vec(x, y)), velocidad(Vec(celeridad, 0.0f)) {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);
  rect.w = PELOTA_ANCHO;
  rect.h = PELOTA_ALTO;
}

void Pelota::Dibujar(SDL_Renderer* renderer) {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);

  SDL_RenderFillRect(renderer, &rect);
}

void Pelota::Actualizar(float dt) { posicion += velocidad * dt; }

std::array<float, 4> Pelota::Vertices() {
  return {posicion.x, posicion.x + PELOTA_ANCHO, posicion.y,
          posicion.y + PELOTA_ALTO};
}

void Pelota::Rebotar() {
  if (preColisionId != colisionId) {
    velocidad.x = -velocidad.x;
    preColisionId = colisionId;
  }
}

void Pelota::Colision(int id) { colisionId = id; }
