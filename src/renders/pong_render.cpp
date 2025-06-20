#include "pong_render.hpp"
#include <format>
#include "../configs.hpp"

PongRender::PongRender(SDL_Window* window, SDL_Renderer* renderer,
                       TTF_Font* fuenteDelPuntaje)
    : window(window), renderer(renderer), fuenteDelPuntaje(fuenteDelPuntaje) {
  SDL_GetWindowSize(window, &width, &height);

  fondo = std::make_unique<Fondo>(renderer, width, height);
  pelota = std::make_unique<Pelota>(renderer, width / 2.0f, height / 2.0f);
  paleta1 = std::make_unique<Paleta>(1, renderer, 50.0f, height / 2.0f);
  paleta2 = std::make_unique<Paleta>(2, renderer, width - 50.0f, height / 2.0f);
  puntaje1 = std::make_unique<PuntajeJugador>(renderer, fuenteDelPuntaje,
                                              Vec(width / 4, 20));
  puntaje2 = std::make_unique<PuntajeJugador>(renderer, fuenteDelPuntaje,
                                              Vec(3 * width / 4, 20));
  input = std::make_unique<Input>();
  contador = std::make_unique<Texto>(renderer, fuenteDelPuntaje, "0.00s",
                                     Alineacion::Centro, Vec((width / 2), 40));
}

PongRender::~PongRender() {}

void PongRender::Dibujar() {
  // Limpia la pantalla en negro
  SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
  SDL_RenderClear(renderer);
  // Actualizo el width y height
  SDL_GetWindowSize(window, &width, &height);

  // Dibujo los objetos
  fondo->Dibujar();
  DibujarRed();

  pelota->Dibujar();

  paleta1->Dibujar();
  paleta2->Dibujar();

  puntaje1->Dibujar();
  puntaje2->Dibujar();
  contador->Dibujar();
}

void PongRender::Iniciar(TipoJugador tipo) {
  estado = PongEstado::SAQUE;
  tiempoInicio = SDL_GetTicks64();
  tiempoEnPausa = 0;
  contador->Actualizar("0.00s");

  input->Reiniciar();
  pelota->Reiniciar(width / 2.0f, height / 2.0f);

  paleta1->Reiniciar(50.0f, height / 2.0f);
  paleta2->Reiniciar(width - 50.0f, height / 2.0f, tipo);

  puntaje1->Reiniciar();
  puntaje2->Reiniciar();
}

void PongRender::Pausar(bool pausar) {
  if (pausar) {
    estado = PongEstado::PAUSAR;
    tiempoEnPausa = SDL_GetTicks64();
  } else {
    estado = PongEstado::EN_JUEGO;
    input->Reiniciar();

    // Adelanto N ms según el tiempo en pausa para que no siga sumando segundos
    tiempoInicio += SDL_GetTicks64() - tiempoEnPausa;
    tiempoEnPausa = 0;
  }
}

Resultado PongRender::ResultadoUltimaPartida() { return resultado; }

bool PongRender::Corriendo() {
  return estado == PongEstado::SAQUE || estado == PongEstado::EN_JUEGO;
}

void PongRender::ActualizarInputs() {
  input->Actualizar();

  if (input->Tecla(Teclas::ENTER) && estado == PongEstado::SAQUE) {
    estado = PongEstado::EN_JUEGO;
  }

  if (input->Tecla(Teclas::ESC)) {
    Pausar(true);
  }
}

void PongRender::Recalcular(double deltaTime) {
  contador->Actualizar(
      std::format("{:.2f}s",
                  (double)(SDL_GetTicks64() - tiempoInicio) / (double)1000.0)
          .c_str());

  if (estado == PongEstado::SAQUE) {
    // Esto es por si al despistarse, se pasa de los 120s. Sacar es parte del
    // juego y corre el tiempo.
    VerificarFin();

    return;
  }
  // Aplico velocidad de movimiento en paletas
  paleta1->AplicarVelocidad(input->Tecla(Teclas::w), input->Tecla(Teclas::s));
  paleta2->AplicarVelocidad(input->Tecla(Teclas::ARRIBA),
                            input->Tecla(Teclas::ABAJO));
  paleta2->AplicarVelocidad(SDL_GetTicks64() - tiempoInicio, pelota.get());

  // Actualizo la posición de cada objeto
  paleta1->Actualizar(deltaTime, height);
  paleta2->Actualizar(deltaTime, height);
  pelota->Actualizar(deltaTime);

  // Verifico posible colisión y corrijo debidamente
  paleta1->Colision(pelota.get());
  paleta2->Colision(pelota.get());

  Contacto contacto = pelota->ColisionConPared(width, height);

  switch (contacto.tipo) {
    case Colision::Izquierda:
      puntaje2->Aumentar();
      paleta1->Reiniciar(50.0f, height / 2.0f);
      paleta2->Reiniciar(width - 50.0f, height / 2.0f);
      estado = PongEstado::SAQUE;
      break;
    case Colision::Derecha:
      puntaje1->Aumentar();
      paleta1->Reiniciar(50.0f, height / 2.0f);
      paleta2->Reiniciar(width - 50.0f, height / 2.0f);
      estado = PongEstado::SAQUE;
      break;
  }

  // Al final del recálculo, verifica si terminó
  VerificarFin();
}

void PongRender::DibujarRed() {
  // Dice a SDL que setee el render con color blanco
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  // Dibuja la red. Mejora implementación del tuto. Itera menos veces.
  for (int y = 0; y < height; y += 5) {
    // Dibuja líneas de [0,3], [5,8]. Siempre con un píxel vacío.
    SDL_RenderDrawLine(renderer, width / 2, y, width / 2, y + 3);
  }
}

void PongRender::FinalizarPartida(bool porCancelado) {
  uint64_t enPausa = tiempoEnPausa > 0 ? SDL_GetTicks64() - tiempoEnPausa : 0;

  estado = PongEstado::FIN;
  resultado = Resultado();

  resultado.tiempo =
      (double)(SDL_GetTicks64() - (tiempoInicio + enPausa)) / (double)1000.0;
  resultado.jugador1 = puntaje1->Puntaje();
  resultado.jugador2 = puntaje2->Puntaje();

  resultado.estado =
      porCancelado                              ? PartidaEstado::QUIT
      : resultado.jugador1 > resultado.jugador2 ? PartidaEstado::JUGADOR_1
      : resultado.jugador2 > resultado.jugador1
          ? TipoJugador::CPU ? PartidaEstado::P_CPU : PartidaEstado::JUGADOR_2
          : PartidaEstado::Empate;
}

PongEstado PongRender::Estado() { return estado; }

// Reglas de la partida
void PongRender::VerificarFin() {
  if (puntaje1->Puntaje() == PUNTAJE_MAXIMO ||
      puntaje2->Puntaje() == PUNTAJE_MAXIMO ||
      ((SDL_GetTicks64() - tiempoInicio) >= TIEMPO_MAXIMO)) {
    FinalizarPartida(false);
  }
}
