#include "puntaje_jugador.hpp"
#include <string>
#include "../configs.hpp"

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

  sonido = Mix_LoadWAV(getAssetsPath("success-340660.mp3").c_str());
  if (sonido == NULL) {
    SDL_Log("Incapaz de inicializar Sonido: %s. Path: %s", SDL_GetError(),
            getAssetsPath("success-340660.mp3").c_str());
  }
}

// Destructor
PuntajeJugador::~PuntajeJugador() {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);

  if (sonido != NULL) {
    Mix_FreeChunk(sonido);
  }
}

void PuntajeJugador::Dibujar() {
  auto status = SDL_RenderCopy(renderer, texture, nullptr, &rect);

  if (status != 0) {
    SDL_Log(SDL_GetError());
  }
}

void PuntajeJugador::Reiniciar() {
  puntaje = 0;

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

int PuntajeJugador::Puntaje() { return puntaje; }

void PuntajeJugador::Aumentar() {
  Mix_PlayChannel(2, sonido, 0);

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
