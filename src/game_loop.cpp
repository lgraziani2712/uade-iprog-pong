#include "game_loop.hpp"
#include <iostream>
#include "configs.hpp"

// https://itp380.org/Lab01.2.html
void gameLoop(SDL_Window* window, SDL_Renderer* renderer,
              PongRender* gameRender) {
  uint64_t tiempoActual = SDL_GetTicks64();
  uint64_t nuevoTiempo = 0;
  // Esta variable permite realizar movimientos y operaciones en nuestro juego
  // tomando el tiempo como referencia y no el frame, así, podemos calcular lo
  // que se mueve algo por segundo en vez de por frame.
  // REGLA: todos los objetos de una escena deberían actualizarse en base al
  // `delta`.
  double deltaBetweenFrames = 0;
  // Serviría si aplicásemos operaciones de animación basadas en tiempo tiempo.
  double tiempoDeJuego = 0;
  // in ms
  const double DELTA_TIME = (1000.0 / (double)APP_FPS);

  while (gameRender->Corriendo()) {
    // 1. Consumir los inputs
    gameRender->ActualizarInputs();

    // 2. Calcular Delta Time
    nuevoTiempo = SDL_GetTicks64();
    deltaBetweenFrames = (double)((nuevoTiempo - tiempoActual) * 1000);
    tiempoActual = nuevoTiempo;
    // Es posible que en ocasiones, esta variable sea mayor al delta de 16ms,
    // pero no quieremos que el render calcule con un delta mayor a esa ventana.
    // Técnicamente, habría que hacer un while hasta que deltaBetweenFrames
    // sea menor a cero en caso de que sea mayor a DELTA_TIME. Pero eso
    // dificultaría el debuggeo.
    double deltaTime =
        deltaBetweenFrames < DELTA_TIME ? deltaBetweenFrames : DELTA_TIME;

    // 3. Actualizar el juego con el delta time en ms.
    gameRender->Recalcular(tiempoDeJuego, deltaTime);
    tiempoDeJuego += deltaTime;

    // 4. Render
    gameRender->Dibujar();
    // Entrega el backbuffer al render
    SDL_RenderPresent(renderer);

    // 5. Dormir el juego hasta el siguiente frame
    SDL_Delay(deltaTime);
  }
}
