#pragma once

enum class Victoria { Empate = 0, JUGADOR_1, JUGADOR_2, QUIT };

struct Resultado {
  Victoria victoria;
  // En segundos
  double tiempo;
  int jugador1, jugador2;
};
