#include "pelota.hpp"
#include <SDL2/SDL_image.h>
#include "../configs.hpp"

Pelota::Pelota(SDL_Renderer* renderer, float x, float y, Mix_Chunk* golpePaleta,
               Mix_Chunk* golpePared)
    // A la posición que recibimos, restamos la mitad del alto y mitad del
    // ancho de la pelota para que ésta esté anclada en su centro
    : posicion(Vec(x, y)),
      velocidad(Vec(celeridad, 0.0f)),
      golpePaleta(golpePaleta),
      golpePared(golpePared),
      renderer(renderer) {
  texture = IMG_LoadTexture(renderer, getAssetsPath("fuego.webp").c_str());

  // Visual
  rect.w = PELOTA_ANCHO;
  rect.h = (PELOTA_ALTO + 12);
}

Pelota::~Pelota() { SDL_DestroyTexture(texture); }

void Pelota::Dibujar() {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);

  if (SDL_RenderCopy(renderer, texture, nullptr, &rect) != 0) {
    SDL_Log(SDL_GetError());
  }
}

void Pelota::Actualizar(float dt) { posicion += velocidad * dt; }

std::array<float, 4> Pelota::Vertices() {
  return {posicion.x, posicion.x + PELOTA_ANCHO, posicion.y,
          posicion.y + PELOTA_ALTO};
}

void Pelota::Colision(Contacto contacto) {
  Mix_PlayChannel(-1, golpePaleta, 0);

  posicion.x += contacto.penetracion;
  velocidad.x = -velocidad.x;

  switch (contacto.tipo) {
    case Colision::Arriba:
      velocidad.y = -.85f * celeridad;
      break;
    case Colision::Abajo:
      velocidad.y = 0.85f * celeridad;
      break;
  }
}

void Pelota::Reiniciar(float x, float y) {
  velocidad = Vec(celeridad, 0.0f);
  posicion = Vec(x, y);
}

Contacto Pelota::ColisionConPared(int windowWidth, int windowHeight) {
  auto vertices = Pelota::Vertices();
  Contacto contacto{};

  // Calculo el contacto que tuvo la pelota
  if (vertices[Lado::Izquierdo] < 0.0f) {
    contacto.tipo = Colision::Izquierda;
  } else if (vertices[Lado::Derecho] > windowWidth) {
    contacto.tipo = Colision::Derecha;
  } else if (vertices[Lado::Arriba] < 0.0f) {
    contacto.tipo = Colision::Arriba;
    contacto.penetracion = -vertices[Lado::Arriba];
  } else if (vertices[Lado::Abajo] > windowHeight) {
    contacto.tipo = Colision::Abajo;
    contacto.penetracion = windowHeight - vertices[Lado::Abajo];
  }

  // Aplico el contacto, corrijo posición y velocidad
  switch (contacto.tipo) {
    case Colision::Arriba:
    case Colision::Abajo:
      Mix_PlayChannel(-1, golpePared, 0);

      posicion.y += contacto.penetracion;
      velocidad.y = -velocidad.y;
      break;
    case Colision::Izquierda:
      posicion.x = windowWidth / 2.0f;
      posicion.y = windowHeight / 2.0f;
      velocidad.x = celeridad;
      velocidad.y = 0.75f * celeridad;
      break;
    case Colision::Derecha:
      posicion.x = windowWidth / 2.0f;
      posicion.y = windowHeight / 2.0f;
      velocidad.x = -celeridad;
      velocidad.y = 0.75f * celeridad;
      break;
  }

  return contacto;
}

Vec Pelota::Velocidad() { return velocidad; }
