#include <SDL2/SDL.h>
#include <functional>

#include "./configs.hpp"
#include "./game_loop.hpp"

void gameLoop(SDL_Renderer* renderer,
              std::function<void(SDL_Renderer* renderer, double deltaTime,
                                 SDL_Event& event)>
                  gameRender) {
  // Esperar a que se cierre la ventana
  bool running = true;
  SDL_Event event;

  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 last = 0;
  // Esta variable permite realizar movimientos y operaciones en nuestro juego
  // tomando el tiempo como referencia y no el frame, así, podemos calcular lo
  // que se mueve algo por segundo en vez de por frame.
  // REGLA: todos los objetos de una escena deberían actualizarse en base al
  // `delta`.
  double deltaTime = 0;

  while (running) {
    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());

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
      //
      SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
      SDL_RenderClear(renderer);

      // Renderizado del frame
      gameRender(renderer, deltaTime, event);

      // Entrega el backbuffer al render
      SDL_RenderPresent(renderer);
    }

    if (deltaTime < APP_FRAME_TARGET_TIME) {
      SDL_Delay((Uint32)((APP_FRAME_TARGET_TIME - deltaTime) * 1000));
    }
  }
}
