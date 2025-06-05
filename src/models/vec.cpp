#include "vec.hpp"

// Constructor que inicializa `x` e `y` en 0.0f
Vec::Vec() : x(0.0f), y(0.0f) {}

// Constructor que recibe los datos de inicialización y los asigna.
Vec::Vec(float x, float y) : x(x), y(y) {}

// Define el operador suma
Vec Vec::operator+(Vec const& rhs) { return Vec(x + rhs.x, y + rhs.y); }
// Define el operador += (suma y asignación)
Vec& Vec::operator+=(Vec const& rhs) {
  x += rhs.x;
  y += rhs.y;

  return *this;
}

// Define el operador multiplicación
Vec Vec::operator*(float rhs) { return Vec(x * rhs, y * rhs); }
// Define el operador *=
Vec& Vec::operator*=(Vec const& rhs) {
  x *= rhs.x;
  y *= rhs.y;

  return *this;
}
