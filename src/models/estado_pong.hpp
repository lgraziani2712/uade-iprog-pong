#pragma once
#include <string>
#include <vector>

enum PartidaEstado { Empate = 0, JUGADOR_1, JUGADOR_2, QUIT };

struct Resultado {
  PartidaEstado estado;
  // En segundos
  double tiempo;
  int jugador1, jugador2;

  Resultado();
  Resultado(std::vector<std::string> datos);
};
