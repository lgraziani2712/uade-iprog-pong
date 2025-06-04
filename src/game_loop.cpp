#include <SDL2/SDL.h>
#include <functional>

#include "./configs.hpp"
#include "./game_loop.hpp"

void gameLoop(SDL_Renderer* renderer, std::function<void(SDL_Renderer* renderer)> game) {
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
      if (event.type == SDL_QUIT) {
        running = false;
      }
    }
    game(renderer);

    if (deltaTime < FRAME_TARGET_TIME) {
      SDL_Delay((Uint32)((FRAME_TARGET_TIME - deltaTime) * 1000));
    }
  }
}
