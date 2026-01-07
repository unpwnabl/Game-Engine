#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <cstdlib>

#include "../../core/misc/include/log.hpp"
#include "../../core/misc/include/colors.h"
#include "../../src/misc/include/resources.h"
#include "include/vector2d.hpp"
#include "include/image.h"

void init_img(int flags) {
	if (IMG_Init(flags) == 0) {
		sdl_error("image.cpp > Couldn't initialize SDL_Image");
	}
	message("SDL_image initialized successfully");
}

Image::Image(SDL_Renderer *renderer, const char* image_path, int x_pos, int y_pos,int width, int height, SDL_Color i_color) : i_renderer(renderer), path(image_path), w(width), h(height), color(i_color) {
	position.x = x_pos;
	position.y = y_pos;
	// Use the resource manager to get surfaces efficently
	SDL_Surface *surface = get_surface(path);
	texture = SDL_CreateTextureFromSurface(i_renderer, surface);
	if (w > 0 && h > 0) {
		rect.w = w;
		rect.h = h;
	} else if (w == 0 && h == 0) {
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	} else {
		error("image.cpp > Incorrect usage of width/height measures");
	}
	rect.x = position.x;
	rect.y = position.y;
	center = {w / 2, h / 2};
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

Image::Image(const Image& img) : i_renderer(img.i_renderer), texture(img.texture), path(img.path), position(img.position), w(img.w), h(img.h), color(img.color) {
	message("Copied image");
}

Image::~Image() {
	if (texture) {
		remove_surface(path);
		SDL_DestroyTexture(texture);
		texture = NULL;
		std::string msg = "Removed image \"" + std::string(path) + "\" from memory";
		message(msg.c_str());
	} else {
		warning("No texture found, already deleted?");
	}
}

Vector2D Image::get_pos() const {
	return position;
}

void Image::set_pos(const Vector2D& n_pos) {
	position = n_pos;
	rect.x = position.x;
	rect.y = position.y;
}

int Image::get_width() const {
	return w;
}

int Image::get_height() const {
	return h;
}

void Image::set_width(int n_w) {
	w = n_w;
	rect.w = w;
	center = {w / 2, h / 2};
}

void Image::set_height(int n_h) {
	h = n_h;
	rect.h = h;
	center = {w / 2, h / 2};
}


SDL_Color Image::get_color() const {
	return color;
}

void Image::set_color(const SDL_Color& n_c) {
	color = n_c;
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

void Image::render() const {
	SDL_RenderCopy(i_renderer, texture, NULL, &rect);
}

void close_img() {
	IMG_Quit();
	message("SDL_image closed");
}
