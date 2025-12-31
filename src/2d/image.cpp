#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <cstdlib>

#include "../../core/misc/include/log.hpp"
#include "../../core/misc/include/colors.h"
#include "../../src/misc/include/resources.h"
#include "include/image.h"

void init_img(int flags) {
	if (IMG_Init(flags) == 0) {
		sdl_error("image.cpp > Couldn't initialize SDL_Image");
	}
	message("SDL_image initialized successfully");
}

Image::Image() {
	error("image.cpp > Please provide correct syntax for Image object. Refer to wiki.md");
};

Image::Image(SDL_Renderer *renderer, const char* image_path, int x_pos, int y_pos,int width, int height) : i_renderer(renderer), path(image_path), x(x_pos), y(y_pos), w(width), h(height) {
	// Use the resource manager to get textures efficently
	texture = get_texture(i_renderer, path);
	if (w > 0 && h > 0) {
		rect.w = w;
		rect.h = h;
	} else if (w == 0 && h == 0) {
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	} else {
		error("image.cpp > Incorrect usage of width/height measures");
	}
	rect.x = x;
	rect.y = y;
	center = {w / 2, h / 2};
}

void Image::set_color(SDL_Color color) const {
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

void Image::render() {
	SDL_RenderCopy(i_renderer, texture, NULL, &rect);
}

Image::~Image() {
	remove_texture(path);
	SDL_DestroyTexture(texture);
	texture = NULL;
	std::string msg = "Removed image \"" + std::string(path) + "\" from memory";
	message(msg.c_str());
}

void close_img() {
	IMG_Quit();
	message("SDL_image closed");
}
