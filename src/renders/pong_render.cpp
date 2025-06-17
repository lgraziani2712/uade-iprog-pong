#include "pong_render.hpp"

PongRender::PongRender(SDL_Window* window, SDL_Renderer* renderer,
                       TTF_Font* fuenteDelPuntaje)
    : window(window), renderer(renderer), fuenteDelPuntaje(fuenteDelPuntaje) {
  SDL_GetWindowSize(window, &width, &height);

  pelota = std::make_unique<Pelota>(width / 2.0f, height / 2.0f);
  paleta1 = std::make_unique<Paleta>(1, 50.0f, height / 2.0f);
  paleta2 = std::make_unique<Paleta>(2, width - 50.0f, height / 2.0f);
  puntaje1 = std::make_unique<PuntajeJugador>(renderer, fuenteDelPuntaje,
                                              Vec(width / 4, 20));
  puntaje2 = std::make_unique<PuntajeJugador>(renderer, fuenteDelPuntaje,
                                              Vec(3 * width / 4, 20));
  input = std::make_unique<Input>();
}

void PongRender::Dibujar() {
  // Limpia la pantalla en negro
  SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
  SDL_RenderClear(renderer);
  // Actualizo el width y height
  SDL_GetWindowSize(window, &width, &height);

  // Dibujo los objetos
  DibujarRed();
  pelota->Dibujar(renderer);
  paleta1->Dibujar(renderer);
  paleta2->Dibujar(renderer);
  puntaje1->Dibujar();
  puntaje2->Dibujar();
}

bool PongRender::Corriendo() { return input->Corriendo(); }

void PongRender::ActualizarInputs() { input->Actualizar(); }

void PongRender::Recalcular(double tiempoTotal, double deltaTime) {
  // Aplico velocidad de movimiento en paletas
  paleta1->AplicarVelocidad(input->Boton(Botones::PaletaUnoArriba),
                            input->Boton(Botones::PaletaUnoAbajo));
  paleta2->AplicarVelocidad(input->Boton(Botones::PaletaDosArriba),
                            input->Boton(Botones::PaletaDosAbajo));

  // Actualizo la posición de cada objeto
  paleta1->Actualizar(deltaTime, height);
  paleta2->Actualizar(deltaTime, height);
  pelota->Actualizar(deltaTime);

  // Verifico posible colisión y corrijo debidamente
  paleta1->Colision(pelota.get());
  paleta2->Colision(pelota.get());
  pelota->ColisionConPared(width, height);
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
