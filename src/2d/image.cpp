#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <cstdlib>

#include "../../core/misc/include/log.hpp"
#include "../../core/misc/include/colors.h"
#include "include/image.h"

Image::Image() {
	error("image.cpp > Please provide correct syntax for Image object. Refer to wiki.md");
};

Image::Image(SDL_Renderer *renderer, const char* image_path, int width, int height) : i_renderer(renderer), path(image_path), w(width), h(height) {
	SDL_Surface *surface = IMG_Load(path);
	if (!surface) {
		sdl_error("image.cpp >");
	}
	message("Loaded image in memory");
	texture = SDL_CreateTextureFromSurface(i_renderer, surface);
	if (w > 0 && h > 0) {
		rect.w = w;
		rect.h = h;
	} else if (w == 0 && h == 0) {
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	} else {
		error("image.cpp > Incorrect usage of width/height measures");
	}
	center = {w / 2, h / 2};
	SDL_FreeSurface(surface);
}

void Image::set_color(SDL_Color color) const {
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

void Image::traslate(int nx, int ny) {
	x = nx;
	y = ny;
}

void Image::rotate(double theta) {
	if (theta >= 360.0) theta -= 360.0;
	SDL_RenderCopyEx(i_renderer, texture, NULL, &rect, theta, &center, SDL_FLIP_NONE);
}

void Image::scale(double factor) {
	h *= factor;
	w *= factor;
}

void Image::reflect() {
	this->rotate(180.0);
}

void Image::render(int x_pos, int y_pos) {
	x = x_pos;
	y = y_pos;
	rect.x = x;
	rect.y = y;
	SDL_RenderCopy(i_renderer, texture, NULL, &rect);
}

Image::~Image() {
	SDL_DestroyTexture(texture);
	texture = NULL;
	std::string msg = "Removed image \"" + std::string(path) + "\" from memory";
	message(msg.c_str());
}
