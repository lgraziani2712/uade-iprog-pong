#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <filesystem>
#include <iostream>
#include <memory>
#include "clean_up.hpp"
#include "configs.hpp"
#include "creation.hpp"
#include "game_loop.hpp"
#include "renders/pong_render.hpp"

std::string getAssetsPath(const std::string& relativePath) {
  namespace fs = std::filesystem;

  // where the binary runs from
  auto base = fs::current_path();

  return (base / "src" / "assets" / relativePath).string();
}

int SDL_main(int argc, char* argv[]) {
  // Inicializa los componentes de SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Incapaz de inicializar SDL: %s", SDL_GetError());
    return 1;
  }
  if (TTF_Init() != 0) {
    SDL_Log("Incapaz de inicializar TTF: %s", TTF_GetError());
    return 1;
  }

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;
  TTF_Font* fuenteDelPuntaje = NULL;

  // Esta variable contiene una instancia de tipo FinalAction (auto le pide al
  // compilador que deduzca automáticamente el tipo de variable). Esta guarda no
  // hace nada excepto esperar a que se cierre el programa. Cuando ocurra el
  // cierre y la instancia se esté por destruir, se invocará la función de
  // cleanUp.
  auto guarda = logicaDeLimpiezaBuild([&]() {
    std::cout << "Limpieza del entorno antes de cerrar.\n";

    if (renderer != NULL) {
      SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
      SDL_DestroyWindow(window);
    }
    if (fuenteDelPuntaje != NULL) {
      TTF_CloseFont(fuenteDelPuntaje);
    }

    SDL_Quit();
  });

  // Instancio las cosas que necesito
  window = createWindow();
  renderer = createRenderer(window);
  fuenteDelPuntaje =
      TTF_OpenFont(getAssetsPath("HurmitNerdFont-Bold.otf").c_str(), 40);
  // Se libera automáticamente al finalizar la función main
  auto gameRender =
      std::make_unique<PongRender>(window, renderer, fuenteDelPuntaje);

  // Inicializo el game loop y paso el puntero a la instancia que renderiza el
  // juego que quiero correr. No muevo el unique_ptr de main.cpp, ya que éste es
  // el owner y es donde se declaran todos los recursos.
  gameLoop(window, renderer, gameRender.get());

  return 0;
}
