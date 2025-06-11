#include "input.hpp"

Input::Input() {}

void Input::Actualizar() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_ESCAPE:
            ejecutando = false;
            break;
          case SDLK_w:
            botones[Botones::PaletaUnoArriba] = true;
            break;
          case SDLK_s:
            botones[Botones::PaletaUnoAbajo] = true;
            break;
          case SDLK_UP:
            botones[Botones::PaletaDosArriba] = true;
            break;
          case SDLK_DOWN:
            botones[Botones::PaletaDosAbajo] = true;
            break;
        }
        break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_w:
            botones[Botones::PaletaUnoArriba] = false;
            break;
          case SDLK_s:
            botones[Botones::PaletaUnoAbajo] = false;
            break;
          case SDLK_UP:
            botones[Botones::PaletaDosArriba] = false;
            break;
          case SDLK_DOWN:
            botones[Botones::PaletaDosAbajo] = false;
            break;
        }
        break;
    }
  }
}

bool Input::Corriendo() { return ejecutando; }

bool Input::Boton(int nombre) { return botones[nombre]; }
