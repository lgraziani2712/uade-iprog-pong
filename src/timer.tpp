#pragma once

#include "timer.hpp"

template <std::intmax_t FPS>
// Inicializa Timer con el actual Timer Point
Timer<FPS>::Timer() : tp{std::chrono::steady_clock::now()} {}

template <std::intmax_t FPS>
void Timer<FPS>::sleep() {
  // Suma el tiempo fijo entre frames al  Time Point
  tp += time_between_frames;

  // Duerme el proceso (y evita consumir cpu) casi hasta el próximo frame
  std::this_thread::sleep_until(tp - std::chrono::nanoseconds(100));

  // menos de 100 nanosegundos de "busy-wait" por precisión
  while (std::chrono::steady_clock::now() < tp) {
  }
}
