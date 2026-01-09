// Thirdparty
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
// C++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
// Game Engine
#include "vars.hpp"
#include "../../core/misc/include/log.hpp"
#include "../../core/misc/include/colors.h"
#include "../../core/misc/include/fps.h"
#include "../../core/misc/include/mouse.h"
#include "../../core/misc/include/events.h"
#include "../../core/ui/include/window.h"
#include "../../core/ui/include/renderer.h"
#include "../../core/ui/include/text.h"
#include "../../core/ui/include/font_paths.hpp"
#include "../../src/2d/include/image.h"
#include "../../src/2d/include/button.h"
#include "../../src/2d/include/vector2d.hpp"
#include "../../src/3d/include/vector3d.hpp"
#include "../../src/misc/include/gameobj.h"
#include "../../src/misc/include/rigidbody.h"

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
	// Initialize text manager
	init_ttf();
	TTF_Font *roboto = TTF_OpenFont(roboto_path, 10);
	// Initialize image manager
	init_img(IMG_INIT_PNG);

	Image sprite(renderer, "imgs/test.png", Vector2D(100, 100), 100, 100);
	sprite.set_color(C_WHITE);
	GameObject player("player", Vector2D(100, 100), 100, 75, std::move(sprite));
	player.rb->set_mass(2.0);

	while (gameloop) {
		// Start counting ticks
		Uint64 start = SDL_GetTicks();
		// Event handler
		event_handler(window, gameloop);
		// Clear previous frame
		renderer_clear(renderer);

		SDL_Rect rect;
		rect.x = 600;
		rect.y = 300;
		rect.w = 50;
		rect.h = 50;
		render_rect(renderer, rect, C_RED);

		render_text(renderer, "Game Engine", roboto, W_W / 2 - 50, W_H / 2 - 50, 25, C_WHITE);
		render_text(renderer, "made by: Unpwnabl", roboto, W_W / 2 - 25, W_H / 2 - 25, 12, C_WHITE);

		player.rb->add_force(Vector2D(1, -2.0));
		player.rb->constrain();

		player.render();
		
		// Cap FPS
		cap(start, MAX_FPS, 1, renderer, roboto);
		// Update renderer
		renderer_update(renderer);
	}
	
	// End program and clean memory
	TTF_CloseFont(roboto);
	close_ttf();
	close_img();
	destroy_renderer(renderer);
	destroy_window(window);

	SDL_Quit();
	success("Program terminated");
}
