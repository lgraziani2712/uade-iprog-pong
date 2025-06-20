#include "fondo.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>
#include "../configs.hpp"

Fondo::Fondo(SDL_Renderer* renderer, int width, int height)
    : renderer(renderer), width(width), height(height) {
  pasto = IMG_LoadTexture(renderer, getAssetsPath("pasto.webp").c_str());
  tierra = IMG_LoadTexture(renderer, getAssetsPath("tierra.webp").c_str());
  roca = IMG_LoadTexture(renderer, getAssetsPath("roca.webp").c_str());

  if (pasto == NULL) {
    SDL_Log(SDL_GetError());
  }
  rect = {0, 0, 64, 64};
};

Fondo::~Fondo() {
  SDL_DestroyTexture(pasto);
  SDL_DestroyTexture(tierra);
  SDL_DestroyTexture(roca);
}

void Fondo::Dibujar() {
  int columns = width / 64;
  int rows = height / 64;
  int rowsRes = width % 64;
  int colRes = height % 64;

  // Pinto de pasto todo menos el marco
  for (int i = 1; i < rows - (rowsRes > 0 ? 1 : 0); i++) {
    rect.y = 64 * i;
    for (int j = 1; j < columns - (colRes > 0 ? 1 : 0); j++) {
      rect.x = 64 * j;

      if (SDL_RenderCopy(renderer, pasto, nullptr, &rect) != 0) {
        SDL_Log(SDL_GetError());
      }
    }
  }

  // Si estoy en la primera o en la última fila, recorro todo el eje X y pinto
  // las rocas
  for (int j = 1; j < columns - (colRes > 0 ? 1 : 0); j++) {
    rect.x = j * 64;

    rect.y = 0;
    if (SDL_RenderCopy(renderer, roca, nullptr, &rect) != 0) {
      SDL_Log(SDL_GetError());
    }

    rect.y = height - 64;
    if (SDL_RenderCopy(renderer, roca, nullptr, &rect) != 0) {
      SDL_Log(SDL_GetError());
    }
  }

  // Si estoy en la primera o en la última columna, recorro todo el eje Y y
  // pinto la tierra
  for (int i = 0; i < rows + (rowsRes > 0 ? 1 : 0) + 1; i++) {
    rect.y = i * 64;

    rect.x = 0;
    if (SDL_RenderCopy(renderer, tierra, nullptr, &rect) != 0) {
      SDL_Log(SDL_GetError());
    }

    rect.x = width - 64;
    if (SDL_RenderCopy(renderer, tierra, nullptr, &rect) != 0) {
      SDL_Log(SDL_GetError());
    }
  }
}
