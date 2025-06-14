#include "game_loop.hpp"
#include <iostream>
#include "configs.hpp"
#include "timer.hpp"

void gameLoop(SDL_Window* window, SDL_Renderer* renderer,
              PongRender* gameRender) {
  uint64_t now = SDL_GetPerformanceCounter();
  uint64_t last = 0;
  // Esta variable permite realizar movimientos y operaciones en nuestro juego
  // tomando el tiempo como referencia y no el frame, así, podemos calcular lo
  // que se mueve algo por segundo en vez de por frame.
  // REGLA: todos los objetos de una escena deberían actualizarse en base al
  // `delta`.
  double deltaTime = 0;

  Timer<APP_FPS> fps_cap_timer;

  while (gameRender->Corriendo()) {
    // 1. Handle input (SDL_PollEvent)
    gameRender->ActualizarInputs();

    // 2. Measure delta time
    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime =
        (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency());

    // 3. Update game state using delta time in seconds
    gameRender->Dibujar(deltaTime);

    // 4. Render
    // Entrega el backbuffer al render
    SDL_RenderPresent(renderer);

    int fps = static_cast<int>(1000.0 / deltaTime);
    std::cout << "FPS: " << fps << "\n";

    fps_cap_timer.sleep();
  }
}
