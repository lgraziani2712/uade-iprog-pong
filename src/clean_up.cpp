#include <functional>

#include "./clean_up.hpp"

AccionFinal::AccionFinal(std::function<void()> fn)
    : hacerLimpieza(std::move(fn)) {}
AccionFinal::~AccionFinal() { hacerLimpieza(); }

AccionFinal logicaDeLimpiezaBuild(std::function<void()> fn) {
  return AccionFinal(std::move(fn));
}
