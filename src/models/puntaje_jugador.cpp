#include "puntaje_jugador.hpp"
#include <string>

PuntajeJugador::PuntajeJugador(SDL_Renderer* renderer, TTF_Font* fuente,
                               Vec posicion)
    : renderer(renderer), fuente(fuente), posicion(posicion) {
  surface = TTF_RenderText_Solid(fuente, "0", {0xFF, 0xFF, 0xFF, 0xFF});
  texture = SDL_CreateTextureFromSurface(renderer, surface);

  int width, height;
  auto status = SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

  if (status != 0) {
    SDL_Log(SDL_GetError());
  }

  rect.x = static_cast<int>(posicion.x);
  rect.y = static_cast<int>(posicion.y);
  rect.w = width;
  rect.h = height;
}

// Destructor
PuntajeJugador::~PuntajeJugador() {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void PuntajeJugador::Dibujar() {
  auto status = SDL_RenderCopy(renderer, texture, nullptr, &rect);

  if (status != 0) {
    SDL_Log(SDL_GetError());
  }
}

void PuntajeJugador::Aumentar() {
  puntaje++;

  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  surface = TTF_RenderText_Solid(fuente, std::to_string(puntaje).c_str(),
                                 {0xFF, 0xFF, 0xFF, 0xFF});
  texture = SDL_CreateTextureFromSurface(renderer, surface);

  int width, height;

  if (SDL_QueryTexture(texture, nullptr, nullptr, &width, &height) != 0) {
    SDL_Log(SDL_GetError());
  }

  rect.w = width;
  rect.h = height;
}
