#include <SDL2/SDL.h>
#include "../../misc/include/error.hpp"
#include "include/window.h"

void create_window(SDL_Window*& window, const char* title, int x, int y, int width, int height) {
	window = SDL_CreateWindow(title, x, y, width, height, SDL_WINDOW_SHOWN);

	if (!window) {
		error("window.cpp > Window couldn't be created");
	}
	success("Window has been created");
	SDL_SetWindowResizable(window, SDL_FALSE);
}

void destroy_window(SDL_Window*& window) {
	if (!window) {
		warning("window.cpp > Window already destroyed...");
	} else {
		SDL_DestroyWindow(window);
		window = NULL;
	}
}
