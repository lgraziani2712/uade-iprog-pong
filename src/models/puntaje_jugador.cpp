#include "puntaje_jugador.hpp"

PuntajeJugador::PuntajeJugador(SDL_Renderer* renderer, TTF_Font* fuente,
                               Vec posicion)
    : renderer(renderer), fuente(fuente), posicion(posicion) {
  surface = TTF_RenderText_Solid(fuente, "0", {0xFF, 0xFF, 0xFF, 0xFF});
  texture = SDL_CreateTextureFromSurface(renderer, surface);

  int width, height;
  SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

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
  SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
