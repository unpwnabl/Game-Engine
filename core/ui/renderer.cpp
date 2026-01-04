#include <SDL2/SDL.h>

#include "../../misc/include/log.hpp"
#include "../../misc/include/colors.h"
#include "include/renderer.h"

void create_renderer(SDL_Window* window, SDL_Renderer*& renderer) {
	// Use VSync and hardware acceleration on render
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		sdl_error("renderer.cpp > Renderer couldn't be created");
	}
	message("Renderer has been created");
	// Set background to black
	SDL_SetRenderDrawColor(renderer, C_BLACK.r, C_BLACK.g, C_BLACK.b, C_BLACK.a);
	SDL_RenderClear(renderer);
}

void render_rect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawRect(renderer, &rect);
}

void renderer_update(SDL_Renderer* renderer) {
	SDL_RenderPresent(renderer);
}

void renderer_clear(SDL_Renderer* renderer) {
	// Clear the previous frame to black
	SDL_SetRenderDrawColor(renderer, C_BLACK.r, C_BLACK.g, C_BLACK.b, C_BLACK.a);
	SDL_RenderClear(renderer);
}

void destroy_renderer(SDL_Renderer*& renderer) {
	if (!renderer) {
		warning("renderer.cpp > Renderer already destroyed...");
	} else {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
}
