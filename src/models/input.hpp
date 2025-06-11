#pragma once

#include <SDL2/SDL.h>

enum Botones {
  PaletaUnoArriba = 0,
  PaletaUnoAbajo,
  PaletaDosArriba,
  PaletaDosAbajo,
};

class Input {
 public:
  Input();
  // Mapea todos los inputs de teclado a los comandos que maneja el juego.
  // Esto corre en cada frame.
  void Actualizar();
  bool Corriendo();
  bool Boton(int nombre);

 private:
  bool botones[4] = {false, false, false, false};
  bool ejecutando = true;
};
