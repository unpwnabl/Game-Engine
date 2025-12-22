#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <cstdlib>

#include "../misc/include/log.hpp"
#include "../misc/include/colors.h"
#include "include/image.h"

Image::Image() {
	error("image.cpp > Please provide correct syntax for Image object");
};

Image::Image(SDL_Renderer *renderer, const char* image_path, int width, int height) : path(image_path), w(width), h(height) {
	SDL_Surface *surface = IMG_Load(path);
	if (!surface) {
		sdl_error("image.cpp >");
	}
	message("Loaded image in memory");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (w > 0 && h > 0) {
		rect.w = w;
		rect.h = h;
	} else if (w == 0 && h == 0) {
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	} else {
		error("image.cpp > Incorrect usage of width/height measures");
	}
	SDL_FreeSurface(surface);
}

void Image::render(SDL_Renderer *renderer, int x_pos, int y_pos) {
	x = x_pos;
	y = y_pos;
	rect.x = x;
	rect.y = y;
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

Image::~Image() {
	SDL_DestroyTexture(texture);
	texture = NULL;
	std::string msg = "Removed image in \"" + std::string(path) + "\" from memory";
	message(msg.c_str());
}
