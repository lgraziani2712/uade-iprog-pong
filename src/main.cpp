#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "clean_up.hpp"
#include "juego.hpp"

int SDL_main(int argc, char* argv[]) {
  // Inicializa los componentes de SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Incapaz de inicializar SDL: %s", SDL_GetError());
    return 1;
  }
  if (TTF_Init() != 0) {
    SDL_Log("Incapaz de inicializar SDL::TTF: %s", TTF_GetError());
    return 1;
  }
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
    SDL_Log("Incapaz de inicializar SDL::Mixer: %s", TTF_GetError());
    return 1;
  }
  if (IMG_Init(IMG_INIT_WEBP) != (IMG_INIT_WEBP)) {
    SDL_Log("Incapaz de inicializar SDL::Image: %s", IMG_GetError());
    return 1;
  }

  // Esta variable contiene una instancia de tipo FinalAction (auto le pide al
  // compilador que deduzca automáticamente el tipo de variable). Esta guarda no
  // hace nada excepto esperar a que se cierre el programa. Cuando ocurra el
  // cierre y la instancia se esté por destruir, se invocará la función de
  // cleanUp.
  auto guarda = logicaDeLimpiezaBuild([&]() {
    SDL_Log("Limpieza del entorno antes de cerrar.\n");

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
  });

  auto instanciaDelJuego = Juego();

  instanciaDelJuego.Init();

  return 0;
}
