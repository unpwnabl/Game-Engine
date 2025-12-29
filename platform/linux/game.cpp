#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>

#include "vars.hpp"
#include "../../core/misc/include/log.hpp"
#include "../../core/misc/include/colors.h"
#include "../../core/misc/include/fps.h"
#include "../../core/ui/include/window.h"
#include "../../core/ui/include/renderer.h"
#include "../../core/ui/include/text.h"
#include "../../core/ui/include/font_paths.hpp"
#include "../../src/2d/include/image.h"

bool gameloop = true;

int main() {
	system("clear");
	debug_b();
	success("Application started");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		error("game.cpp > Couldn't initialize SDL: ");
	}
	// Create the window
	SDL_Window *window = NULL;
	create_window(window, "Test", W_W, W_H);
	// Create the renderer
	SDL_Renderer *renderer;
	create_renderer(window, renderer);
	// Initialize text management
	init_ttf();
	TTF_Font *roboto = TTF_OpenFont(roboto_path, 10);

	Image test(renderer, "imgs/test.png", 100, 100);
	Image test2(renderer, "imgs/test.png", 100, 100);
	test2.set_color(C_RED);

	while (gameloop) {
		// Start counting ticks
		Uint64 start = SDL_GetTicks();

		// Event handler
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				gameloop = false;
			}
		}
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE]) {
			gameloop = false;
		}
		renderer_clear(renderer);

		SDL_Rect rect;
		rect.x = 600;
		rect.y = 300;
		rect.w = 50;
		rect.h = 50;
		render_rect(renderer, rect, C_RED);

		render_text(renderer, "Game Engine", roboto, W_W / 2 - 50, W_H / 2 - 50, 25, C_WHITE);
		render_text(renderer, "made by: Unpwnabl", roboto, W_W / 2 - 25, W_H / 2 - 25, 12, C_WHITE);

		test2.render(120, 120);
		test.render(100, 100);
		test.rotate(1.0 * delta_time);

		cap(start, MAX_FPS, 1, renderer, roboto);
	
		// Update renderer
		renderer_update(renderer);
	}
	
	// End program while cleaning memory
	TTF_CloseFont(roboto);
	close_ttf();
	destroy_renderer(renderer);
	destroy_window(window);

	SDL_Quit();
	success("Program terminated");
}
