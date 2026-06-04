#ifndef MOUSE_H
#define MOUSE_H

#include <SDL2/SDL.h>

#include "../../../src/2d/include/vector2d.hpp"

extern bool mouse_is_clicked;
extern Vector2D mouse_position;
extern Vector2D mouse_click;
extern Vector2D mouse_left_click;
extern Vector2D mouse_right_click;

Vector2D get_mouse_position(SDL_MouseMotionEvent& event);
Vector2D mouse_clicked(SDL_MouseButtonEvent& event);

#endif
