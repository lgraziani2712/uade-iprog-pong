#pragma once

enum class Colision { Nada = 0, Arriba, Centro, Abajo, Izquierda, Derecha };
enum Lado { Izquierdo = 0, Derecho, Arriba, Abajo };

struct Contacto {
  Colision tipo;
  float penetracion;
};
