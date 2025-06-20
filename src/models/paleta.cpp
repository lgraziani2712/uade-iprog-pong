#include "paleta.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../configs.hpp"

Paleta::Paleta(int id, SDL_Renderer* renderer, float x, float y)
    : posicion(Vec(x - PALETA_ANCHO / 2.0f, y - PALETA_ALTO / 2.0f)),
      velocidad(Vec(0.0f, 0.0f)),
      renderer(renderer),
      id(id) {
  rect.x = static_cast<int>(posicion.x);
  rect.w = PALETA_ANCHO;
  rect.h = PALETA_ALTO;

  texture = IMG_LoadTexture(renderer, getAssetsPath("basalto.webp").c_str());
}

Paleta::~Paleta() { SDL_DestroyTexture(texture); }

void Paleta::Dibujar() {
  rect.y = static_cast<int>(posicion.y);

  if (SDL_RenderCopy(renderer, texture, nullptr, &rect) != 0) {
    SDL_Log(SDL_GetError());
  }
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

void Paleta::Reiniciar(float x, float y) {
  velocidad = Vec(0.0f, 0.0f);
  posicion = Vec(x - PALETA_ANCHO / 2.0f, y - PALETA_ALTO / 2.0f);
  rect.x = static_cast<int>(posicion.x);
}

void Paleta::Colision(Pelota* pelota) {
  auto verticesPelota = pelota->Vertices();
  float vertices[4] = {posicion.x, posicion.x + PALETA_ANCHO, posicion.y,
                       posicion.y + PALETA_ALTO};
  // TODO: Usar SDL_IntersectRect
  Contacto contacto{};

  contacto.id = id;

  if ((verticesPelota[Lado::Izquierdo] > vertices[Lado::Derecho]) ||
      (verticesPelota[Lado::Derecho] < vertices[Lado::Izquierdo]) ||
      (verticesPelota[Lado::Arriba] > vertices[Lado::Abajo]) ||
      (verticesPelota[Lado::Abajo] < vertices[Lado::Arriba])) {
    return;
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
  } else if ((verticesPelota[Lado::Abajo] >= rangoSuperior) &&
             (verticesPelota[Lado::Abajo] <= rangoMedio)) {
    contacto.tipo = Colision::Centro;
  } else {
    contacto.tipo = Colision::Abajo;
  }

  pelota->Colision(contacto);
}
