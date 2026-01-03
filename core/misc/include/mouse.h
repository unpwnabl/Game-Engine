#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>

#include "../../../src/2d/include/vector2d.hpp"

extern Vector2D position;
extern Vector2D click;
extern Vector2D left_click;
extern Vector2D right_click;

Vector2D get_position(SDL_MouseMotionEvent& event);
Vector2D clicked(SDL_MouseButtonEvent& event);

#endif
