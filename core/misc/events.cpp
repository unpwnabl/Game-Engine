#include <SDL2/SDL.h>

#include <iostream>

#include "include/events.h"
#include "include/log.hpp"
#include "include/mouse.h"

void event_handler(SDL_Window* window, bool& gl) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			// Mouse click
			clicked(event.button);
			// std::cout << "Mouse clicked at: " << click.x << ", " << click.y << std::endl;
		} else if (event.type == SDL_MOUSEMOTION) {
			// Mouse motion
			get_position(event.motion);
			// std::cout << "Mouse moved to: " << position.x << ", " << position.y << std::endl;
		}
		// Exit
		if (event.type == SDL_QUIT) {
			gl = false;
		}
	}
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		gl = false;
	}
}
