#include "texto.hpp"

Texto::Texto(SDL_Renderer* renderer, TTF_Font* fuente, const char* texto,
             Vec posicion)
    : renderer(renderer), fuente(fuente), posicion(posicion) {
  surface = TTF_RenderText_Solid(fuente, texto, {0xFF, 0xFF, 0xFF, 0xFF});

  if (surface == NULL) {
    SDL_Log(SDL_GetError());
  }
  texture = SDL_CreateTextureFromSurface(renderer, surface);

  if (texture == NULL) {
    SDL_Log(SDL_GetError());
  }

  int width, height;

  if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
    SDL_Log(SDL_GetError());
  }

  rect.w = width;
  rect.h = height;
  rect.x = static_cast<int>(posicion.x) - (width / 2);
  rect.y = static_cast<int>(posicion.y) - (height / 2);
}

// Destructor
Texto::~Texto() {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void Texto::Actualizar(const char* texto) {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  surface = TTF_RenderText_Solid(fuente, texto, {0xFF, 0xFF, 0xFF, 0xFF});
  texture = SDL_CreateTextureFromSurface(renderer, surface);

  int width, height;

  if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
    SDL_Log(SDL_GetError());
  }

  rect.x = static_cast<int>(posicion.x) - (width / 2);
  rect.y = static_cast<int>(posicion.y) - (height / 2);
  rect.w = width;
  rect.h = height;
}

void Texto::Dibujar() {
  if (SDL_RenderCopy(renderer, texture, nullptr, &rect) != 0) {
    SDL_Log(SDL_GetError());
  }
}
