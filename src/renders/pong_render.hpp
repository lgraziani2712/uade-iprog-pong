#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "../models/paleta.hpp"
#include "../models/pelota.hpp"
#include "../models/puntaje_jugador.hpp"

class PongRender {
 public:
  PongRender(SDL_Window* window, SDL_Renderer* renderer,
             TTF_Font* fuenteDelPuntaje);
  void Dibujar(double deltaTime, SDL_Event& event);

 private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* fuenteDelPuntaje;
  int width, height;

  // La estructura de unique_ptr (pointer) nos permite configurar punteros
  // constantes (no temporales). La implementación anterior usaba punteros
  // crudos, por ejemplo, Pelota*.
  // Esta solución fue realizada junto con chapgpt.
  std::unique_ptr<Pelota> pelota;
  std::unique_ptr<Paleta> paleta1;
  std::unique_ptr<Paleta> paleta2;
  std::unique_ptr<PuntajeJugador> puntaje1;
  std::unique_ptr<PuntajeJugador> puntaje2;

  void DibujarRed();
};
