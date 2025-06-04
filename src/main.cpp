#include <SDL2/SDL.h>
#include <iostream>

#include "./clean_up.hpp"
#include "./configs.hpp"
#include "./creation.hpp"
#include "./game_loop.hpp"
#include "./logic/red_window.hpp"

int SDL_main(int argc, char* argv[]) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return 1;
  }
  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  // Esta variable contiene una instancia de tipo FinalAction (auto le pide al
  // compilador que deduzca automáticamente el tipo de variable). Esta guarda no
  // hace nada excepto esperar a que se cierre el programa. Cuando ocurra el
  // cierre y la instancia se esté por destruir, se invocará la función de
  // cleanUp.
  auto guard = cleanUpCreation([&]() {
    std::cout << "Cleaning up before shutdown.\n";

    if (renderer != NULL) {
      SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
      SDL_DestroyWindow(window);
    }
    SDL_Quit();
  });

  // Instancio las cosas que necesito
  window = createWindow();
  renderer = createRenderer(window);

  gameLoop(renderer, redWindowGame);

  return 0;
}
