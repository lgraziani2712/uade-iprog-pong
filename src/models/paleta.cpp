#include "paleta.hpp"
#include <iostream>

Paleta::Paleta(int id, float x, float y)
    : posicion(Vec(x, y - PALETA_ALTO / 2.0f)),
      velocidad(Vec(0.0f, 0.0f)),
      id(id) {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);
  rect.w = PALETA_ANCHO;
  rect.h = PALETA_ALTO;
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
  } else if (posicion.y > (height - PALETA_ALTO)) {
    // Limita al borde inferior
    posicion.y = height - PALETA_ALTO;
  }
}

Contacto Paleta::VerificarColision(Pelota* pelota) {
  auto verticesPelota = pelota->Vertices();
  float vertices[4] = {posicion.x, posicion.x + PALETA_ANCHO, posicion.y,
                       posicion.y + PALETA_ALTO};
  Contacto contacto{};

  if ((verticesPelota[Lado::Izquierdo] > vertices[Lado::Derecho]) ||
      (verticesPelota[Lado::Derecho] < vertices[Lado::Izquierdo]) ||
      (verticesPelota[Lado::Arriba] > vertices[Lado::Abajo]) ||
      (verticesPelota[Lado::Abajo] < vertices[Lado::Arriba])) {
    return contacto;
  }
  float rangoSuperior = vertices[Lado::Abajo] - (2.0f * PALETA_ALTO / 3.0f);
  float rangoMedio = vertices[Lado::Abajo] - (PALETA_ALTO / 3.0f);

  if (pelota->Velocidad().x < 0) {
    // Paleta izquierda
    contacto.penetracion =
        vertices[Lado::Derecho] - verticesPelota[Lado::Izquierdo];
  } else if (pelota->Velocidad().x > 0) {
    // Paleta derecha
    contacto.penetracion =
        vertices[Lado::Izquierdo] - verticesPelota[Lado::Derecho];
  }

  if ((verticesPelota[Lado::Abajo] > vertices[Lado::Arriba]) &&
      (verticesPelota[Lado::Abajo] < rangoSuperior)) {
    contacto.tipo = Colision::Arriba;
  } else if ((verticesPelota[Lado::Abajo] > rangoSuperior) &&
             (verticesPelota[Lado::Abajo] < rangoMedio)) {
    contacto.tipo = Colision::Centro;
  } else {
    contacto.tipo = Colision::Abajo;
  }

  return contacto;
}
