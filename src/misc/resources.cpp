#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <unordered_map>

#include "../../core/misc/include/log.hpp"
#include "include/resources.h"

std::unordered_map<const char*, SDL_Texture*> map;

SDL_Texture* get_texture(SDL_Renderer* renderer, const char* path) {
	auto search = map.find(path);
	if (search != map.end()) {
		std::string msg = "Found texture from \"" + std::string(path) + "\", loading";
		warning(msg.c_str());
		return map[path];
	} else {
		std::string msg = "First instance of texture from \"" + std::string(path) + "\", loading and adding to map";
		warning(msg.c_str());
		SDL_Surface *surface = IMG_Load(path);
		if (!surface) {
			sdl_error("resources.cpp >");
		}
		message("Loaded image in memory");
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		message("Saved image in map");
		map.insert(std::make_pair(path, texture));
		return texture;
	}
}

void remove_texture(const char* path) {
	auto search = map.find(path);
	if (search != map.end()) {
		message("Removing image from map");
		map.erase(search);
	}
}
