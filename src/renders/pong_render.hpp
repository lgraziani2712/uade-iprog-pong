#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "../models/estado_pong.hpp"
#include "../models/fondo.hpp"
#include "../models/input.hpp"
#include "../models/paleta.hpp"
#include "../models/pelota.hpp"
#include "../models/puntaje_jugador.hpp"
#include "../models/texto.hpp"

const enum PongEstado { SAQUE, EN_JUEGO, PAUSAR, FIN };

class PongRender {
 public:
  PongRender(SDL_Window* window, SDL_Renderer* renderer,
             TTF_Font* fuenteDelPuntaje);
  ~PongRender();
  bool Corriendo();
  void ActualizarInputs();
  void Recalcular(double deltaTime);
  void Dibujar();
  void Iniciar(TipoJugador tipo);
  Resultado ResultadoUltimaPartida();
  void FinalizarPartida(bool porCancelado);
  PongEstado Estado();
  void Pausar(bool pausar);

 private:
  const uint64_t TIEMPO_MAXIMO = 120000;
  const int PUNTAJE_MAXIMO = 7;
  uint64_t tiempoInicio = 0;
  uint64_t tiempoEnPausa = 0;
  PongEstado estado = PongEstado::FIN;
  PongEstado estadoPrePausa;
  Resultado resultado;

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
  std::unique_ptr<Input> input;
  std::unique_ptr<Texto> contador;
  std::unique_ptr<Fondo> fondo;

  void DibujarRed();
  void VerificarFin();
};
