#pragma once

#include <SDL2/SDL.h>
#include <functional>

void gameLoop(SDL_Renderer* renderer, std::function<void(SDL_Renderer* renderer)> game);
