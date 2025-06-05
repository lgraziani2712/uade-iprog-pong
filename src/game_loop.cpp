#include <SDL2/SDL.h>
#include <functional>

#include "./configs.hpp"
#include "game_loop.hpp"

void gameLoop(SDL_Window* window, SDL_Renderer* renderer,
              PongRender gameRender) {
  // Esperar a que se cierre la ventana
  bool running = true;
  SDL_Event event;

  uint64_t now = SDL_GetPerformanceCounter();
  uint64_t last = 0;
  // Esta variable permite realizar movimientos y operaciones en nuestro juego
  // tomando el tiempo como referencia y no el frame, así, podemos calcular lo
  // que se mueve algo por segundo en vez de por frame.
  // REGLA: todos los objetos de una escena deberían actualizarse en base al
  // `delta`.
  double deltaTime = 0;

  while (running) {
    // 1. Handle input (SDL_PollEvent)
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) {
            running = false;
          }
          break;
      }

      // 2. Measure delta time
      last = now;
      now = SDL_GetPerformanceCounter();
      deltaTime =
          (now - last) / static_cast<double>(SDL_GetPerformanceFrequency());

      // 3. Update game state using delta time
      gameRender.Dibujar(renderer, deltaTime, event);

      // 4. Render
      // Entrega el backbuffer al render
      SDL_RenderPresent(renderer);
    }

    if (deltaTime < APP_FRAME_TARGET_TIME) {
      // Timing: el manejo del timing es crucial en el funcionamiento del game
      // loop porque tiene un impacto directo en la experiencia del jugador.
      SDL_Delay(
          static_cast<Uint32>((APP_FRAME_TARGET_TIME - deltaTime) * 1000));
    }
  }
}
