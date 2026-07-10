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
#include "../../core/misc/include/keyboard.h"
#include "../../core/misc/include/events.h"
#include "../../core/misc/include/matrix.hpp"
#include "../../core/ui/include/window.h"
#include "../../core/ui/include/renderer.h"
#include "../../core/ui/include/text.h"
#include "../../core/ui/include/font_paths.hpp"
#include "../../src/2d/include/image.h"
#include "../../src/2d/include/polygons.h"
#include "../../src/2d/include/spritesheet.h"
#include "../../src/2d/include/vector2d.hpp"
#include "../../src/3d/include/vector3d.hpp"
#include "../../src/3d/include/solids.h"
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
	create_window(window, "Function Plotter", 0, 0, W_W, W_H, SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
	// Create the renderer
	SDL_Renderer *renderer;
	create_renderer(window, renderer);
	// Initialize text manager
	init_ttf();
	TTF_Font *roboto = TTF_OpenFont(roboto_path, 10);
	// Initialize image manager for PNG format
	init_img(IMG_INIT_PNG);

	float points[] = {-100, -75, 0, 50, 25, 10, 30, 100, -100, -75, 0, 50, 25, 10, 30, 100, -100, -75, 0, 50, 25, 10, 30, 100,};
	int n_points = 24;

	int pos = 0;
	int step = (int)W_W / n_points;

	Vector2D vertex[n_points];

	for (int i = 0; i < n_points; i++) {
		vertex[i] = Vector2D(pos, points[i] + W_H / 2);
		pos += step;
	}

	while (gameloop) {
		// Start counting ticks
		Uint64 start = SDL_GetTicks();
		// Event handler
		event_handler(window, gameloop);
		// Clear previous frame
		renderer_clear(renderer);

		// X axis
		line(renderer, Vector2D(0, W_H / 2), Vector2D(W_W, W_H / 2));
		// Y axis
		line(renderer, Vector2D(W_W / 2, 0), Vector2D(W_W / 2, W_H));
		
		// Render points and connect them
		for (int i = 0; i < n_points; i++) {
			if (i + 1 != n_points) {
				connect(renderer, vertex[i], vertex[i + 1], C_BLUE);
			}
			point(renderer, vertex[i], C_RED);
		}

		// Cap FPS
		cap(start, MAX_FPS, true, renderer, roboto);
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
	success("Application terminated");
}
