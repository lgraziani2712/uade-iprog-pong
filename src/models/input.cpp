#include "input.hpp"

Input::Input() {}

void Input::Actualizar() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_RETURN:
            teclas[Teclas::ENTER] = true;
            break;
          case SDLK_ESCAPE:
            teclas[Teclas::ESC] = true;
            break;
          case SDLK_w:
            teclas[Teclas::w] = true;
            break;
          case SDLK_s:
            teclas[Teclas::s] = true;
            break;
          case SDLK_UP:
            teclas[Teclas::ARRIBA] = true;
            break;
          case SDLK_DOWN:
            teclas[Teclas::ABAJO] = true;
            break;
        }
        break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_RETURN:
            teclas[Teclas::ENTER] = false;
            break;
          case SDLK_ESCAPE:
            teclas[Teclas::ESC] = false;
            break;
          case SDLK_w:
            teclas[Teclas::w] = false;
            break;
          case SDLK_s:
            teclas[Teclas::s] = false;
            break;
          case SDLK_UP:
            teclas[Teclas::ARRIBA] = false;
            break;
          case SDLK_DOWN:
            teclas[Teclas::ABAJO] = false;
            break;
        }
        break;
    }
  }
}

bool Input::Tecla(int nombre) { return teclas[nombre]; }

void Input::Reiniciar() {
  for (int i = 0; i < 6; i++) {
    teclas[i] = false;
  }
}
