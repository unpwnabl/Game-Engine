#include <SDL2/SDL.h>

#include "include/mouse.h"

class Vector2D;

bool is_clicked;
Vector2D position;
Vector2D click;
Vector2D left_click;
Vector2D right_click;

Vector2D get_position(SDL_MouseMotionEvent& event) {
	position.x = event.x;
	position.y = event.y;
	return Vector2D(event.x, event.y);
}

Vector2D clicked(SDL_MouseButtonEvent& event) {
	if (event.button == SDL_BUTTON_LEFT) {
		if (event.state == SDL_PRESSED) {
			left_click.x = event.x;
			left_click.y = event.y;
			click.x = event.x;
			click.y = event.y;
			is_clicked = true;
		 } else if (event.state == SDL_RELEASED) {
			is_clicked = false;
		 }
	} else if (event.button == SDL_BUTTON_RIGHT) {
		if (event.state == SDL_PRESSED) {
			right_click.x = event.x;
			right_click.y = event.y;
			click.x = event.x;
			click.y = event.y;
			is_clicked = true;
		} else if (event.state == SDL_RELEASED) {
			is_clicked = false;
		}
	}
return Vector2D(event.x, event.y);
}
