#pragma once

#include <chrono>
#include <cstdint>
#include <thread>
#include <type_traits>

// Fuente: https://stackoverflow.com/a/77744852/2862917
template <std::intmax_t FPS>
class Timer {
 public:
  Timer();
  void sleep();

 private:
  using FrameDuration = std::chrono::duration<double, std::ratio<1, FPS>>;
  // Duración fija y constante de 1/FPS segundos
  static constexpr FrameDuration time_between_frames{1};

  // Timer Point: "punto en el tiempo" que tenemos para cada frame
  std::chrono::time_point<std::chrono::steady_clock, FrameDuration> tp;
};

#include "timer.tpp"
