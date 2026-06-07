#include <SDL2/SDL.h>

#include <iostream>

#include "include/events.h"
#include "include/log.hpp"
#include "include/mouse.h"
#include "include/keyboard.h"

void event_handler(SDL_Window* window, bool& gl) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		// Keyboard
		update_key(event);

		// Mouse
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			// Mouse click
			mouse_clicked(event.button);
			// std::cout << "Mouse clicked at: " << click.x << ", " << click.y << std::endl;
		} else if (event.type == SDL_MOUSEMOTION) {
			// Mouse motion
			get_mouse_position(event.motion);
			// std::cout << "Mouse moved to: " << position.x << ", " << position.y << std::endl;
		}
		// Exit
		if (event.type == SDL_QUIT) {
			gl = false;
		}
	}

	if (scancode == SDL_SCANCODE_ESCAPE) {
		gl = false;
	}
}
