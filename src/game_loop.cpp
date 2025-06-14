#include "game_loop.hpp"
#include <iostream>
#include "configs.hpp"
#include "timer.hpp"

void gameLoop(SDL_Window* window, SDL_Renderer* renderer,
              PongRender* gameRender) {
  uint64_t tiempoActual = SDL_GetPerformanceCounter();
  uint64_t nuevoTiempo = 0;
  // Esta variable permite realizar movimientos y operaciones en nuestro juego
  // tomando el tiempo como referencia y no el frame, así, podemos calcular lo
  // que se mueve algo por segundo en vez de por frame.
  // REGLA: todos los objetos de una escena deberían actualizarse en base al
  // `delta`.
  double tiempoDelFrame = 0;
  double tiempo = 0;
  const double DELTA_TIME = (1.0 / (double)APP_FPS) * 1000.0;

  Timer<APP_FPS> fps_cap_timer;

  while (gameRender->Corriendo()) {
    // 1. Consumir los inputs
    gameRender->ActualizarInputs();

    // 2. Calcular Delta Time
    // Basado en https://gafferongames.com/post/fix_your_timestep/
    nuevoTiempo = SDL_GetPerformanceCounter();
    tiempoDelFrame = (double)((nuevoTiempo - tiempoActual) * 1000 /
                              (double)SDL_GetPerformanceFrequency());
    tiempoActual = nuevoTiempo;

    // Técnicamente, habría que hacer un while hasta que tiempoDelFrame
    // sea menor a cero en caso de que sea mayor a DELTA_TIME. Pero eso
    // dificultaría el debuggeo.
    double variableDt =
        tiempoDelFrame < DELTA_TIME ? tiempoDelFrame : DELTA_TIME;

    // 3. Actualizar el juego con el delta time en ms.
    gameRender->Recalcular(tiempo, variableDt);
    tiempo += variableDt;

    // 4. Render
    gameRender->Dibujar();
    // Entrega el backbuffer al render
    SDL_RenderPresent(renderer);

    // 5. Dormir el juego hasta el siguiente frame
    fps_cap_timer.sleep();
  }
}
