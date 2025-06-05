#pragma once

#include <SDL2/SDL.h>
#include <functional>
#include <memory>

#include "./renders/pong_render.hpp"

void gameLoop(SDL_Window* window, SDL_Renderer* renderer,
              PongRender* gameRender);
