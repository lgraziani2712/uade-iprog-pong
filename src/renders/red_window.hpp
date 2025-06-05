#pragma once

#include <SDL2/SDL.h>

void redWindowGameRender(SDL_Window* window, SDL_Renderer* renderer,
                         double deltaTime, SDL_Event& event);
