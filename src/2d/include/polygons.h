#ifndef POLYGONS_H
#define POLYGONS_H

#include <SDL2/SDL.h>

#include "../../../core/misc/include/colors.h"
#include "vector2d.hpp"

void rect(SDL_Renderer* renderer, Vector2D pos, int w, int h, SDL_Color fcolor = C_WHITE, bool filled = false);

void point(SDL_Renderer* renderer, Vector2D pos, SDL_Color fcolor = C_WHITE);

void line(SDL_Renderer* renderer, Vector2D pos1, Vector2D pos2, SDL_Color fcolor = C_WHITE);

#endif
