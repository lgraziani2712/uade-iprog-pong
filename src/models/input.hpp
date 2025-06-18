#pragma once

#include <SDL2/SDL.h>

enum Teclas { w = 0, s, ARRIBA, ABAJO, ENTER, ESC };

class Input {
 public:
  Input();
  // Mapea todos los inputs de teclado a los comandos que maneja el juego.
  // Esto corre en cada frame.
  void Actualizar();
  bool Tecla(int nombre);
  void Reiniciar();

 private:
  bool teclas[6] = {false, false, false, false, false, false};
};
