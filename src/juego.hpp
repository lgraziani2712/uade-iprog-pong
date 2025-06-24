#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include "models/input.hpp"
#include "renders/pong_render.hpp"

const enum JuegoEstado { MENU, PLAY, PAUSA, FINALIZADO, RANKING, EXIT };

class Juego {
 public:
  Juego();
  ~Juego();

  void Init();

 private:
  int width, height;
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* fuente;
  TTF_Font* autorFuente;
  TTF_Font* fuenteTitulo;
  Mix_Chunk* menuOpcion;
  Mix_Chunk* menuSeleccion;

  std::unique_ptr<PongRender> render;
  std::unique_ptr<Input> input;

  JuegoEstado estado = JuegoEstado::MENU;

  void Menu();
  void Play();
  void Pausa();
  void Finalizado();
  void Ranking();
};
