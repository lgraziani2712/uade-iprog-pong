#pragma once

#include <SDL2/SDL.h>
#include "colision.hpp"
#include "input.hpp"
#include "pelota.hpp"
#include "vec.hpp"

#define PALETA_ANCHO 30
#define PALETA_ALTO 120

const enum TipoJugador { PERSONA, CPU };
const enum PaletaMovimiento { QUIETA, SUBE, BAJA };

class Paleta {
 public:
  Paleta(int id, SDL_Renderer* renderer, float x, float y);
  ~Paleta();

  void Dibujar();
  void AplicarVelocidad(bool arriba, bool abajo);
  void AplicarVelocidad(uint64_t tiempo, Pelota* pelota);
  void Actualizar(float dt, int height);
  void Colision(Pelota* pelota);
  void Reiniciar(float x, float y, TipoJugador tipo);
  void Reiniciar(float x, float y);

 private:
  TipoJugador tipo = TipoJugador::PERSONA;
  PaletaMovimiento movimiento = PaletaMovimiento::QUIETA;

  float celeridad = 1.0f;
  uint64_t tiempoInicio = -1;
  int id;
  Vec posicion;
  Vec velocidad;
  SDL_Rect rect{};
  SDL_Renderer* renderer;
  SDL_Texture* texture;
};
