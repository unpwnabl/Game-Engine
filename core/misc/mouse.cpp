#include <SDL2/SDL.h>

#include "include/mouse.h"

class Vector2D;

bool mouse_is_clicked;
Vector2D mouse_position;
Vector2D mouse_click;
Vector2D mouse_left_click;
Vector2D mouse_right_click;

Vector2D get_mouse_position(SDL_MouseMotionEvent& event) {
	mouse_position.x = event.x;
	mouse_position.y = event.y;
	return Vector2D(event.x, event.y);
}

Vector2D mouse_clicked(SDL_MouseButtonEvent& event) {
	if (event.button == SDL_BUTTON_LEFT) {
		if (event.state == SDL_PRESSED) {
			mouse_left_click.x = event.x;
			mouse_left_click.y = event.y;
			mouse_click.x = event.x;
			mouse_click.y = event.y;
			mouse_is_clicked = true;
		 } else if (event.state == SDL_RELEASED) {
			mouse_is_clicked = false;
		 }
	} else if (event.button == SDL_BUTTON_RIGHT) {
		if (event.state == SDL_PRESSED) {
			mouse_right_click.x = event.x;
			mouse_right_click.y = event.y;
			mouse_click.x = event.x;
			mouse_click.y = event.y;
			mouse_is_clicked = true;
		} else if (event.state == SDL_RELEASED) {
			mouse_is_clicked = false;
		}
	}
	return Vector2D(event.x, event.y);
}
