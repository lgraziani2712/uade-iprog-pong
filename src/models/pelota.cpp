#include "pelota.hpp"
#include <SDL2/SDL_image.h>
#include "../configs.hpp"

Pelota::Pelota(SDL_Renderer* renderer, float x, float y)
    : posicion(Vec(x - PELOTA_ANCHO / 2.0f, y - PELOTA_ALTO / 2.0f)),
      velocidad(Vec(celeridad, 0.0f)),
      renderer(renderer) {
  texture = IMG_LoadTexture(renderer, getAssetsPath("fuego.webp").c_str());

  golpe = Mix_LoadWAV(getAssetsPath("short-fire-whoosh_1-317280.mp3").c_str());
  if (golpe == NULL) {
    SDL_Log("Incapaz de inicializar Sonido: %s. Path: %s", SDL_GetError(),
            getAssetsPath("short-fire-whoosh_1-317280.mp3").c_str());
  }

  // Visual
  rect.w = PELOTA_ANCHO;
  rect.h = (PELOTA_ALTO + 12);
}

Pelota::~Pelota() {
  if (texture != NULL) {
    SDL_DestroyTexture(texture);
  }
  if (golpe != NULL) {
    Mix_FreeChunk(golpe);
  }
}

void Pelota::Dibujar() {
  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y) - 12;

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
  // En el extremo caso de que se pause en el frame de la colisión, al despausar
  // va a volver a verificar la colisión (que efectivamente fue, y va a invertir
  // el contacto, cosa que no queremos). Esta guarda previene que se ejecute una
  // colisión dos veces en dos frames.
  if (idContacto == contacto.id) {
    return;
  }
  if (contacto.tipo == Colision::Nada) {
    idContacto = -1;

    return;
  }
  idContacto = contacto.id;
  Mix_PlayChannel(-1, golpe, 0);

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
  posicion = Vec(x - PELOTA_ANCHO / 2.0f, y - PELOTA_ALTO / 2.0f);
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
      Mix_PlayChannel(-1, golpe, 0);

      posicion.y += contacto.penetracion;
      velocidad.y = -velocidad.y;
      break;
    case Colision::Izquierda:
      posicion.x = (windowWidth - PELOTA_ANCHO) / 2.0f;
      posicion.y = (windowHeight - PELOTA_ALTO) / 2.0f;
      velocidad.x = celeridad;
      velocidad.y = 0.75f * celeridad;
      break;
    case Colision::Derecha:
      posicion.x = (windowWidth - PELOTA_ANCHO) / 2.0f;
      posicion.y = (windowHeight - PELOTA_ALTO) / 2.0f;
      velocidad.x = -celeridad;
      velocidad.y = 0.75f * celeridad;
      break;
  }

  return contacto;
}

Vec Pelota::Velocidad() { return velocidad; }
