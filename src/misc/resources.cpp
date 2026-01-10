#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <string>
#include <unordered_map>
#include <iostream>

#include "../../core/misc/include/log.hpp"
#include "include/resources.h"

std::unordered_map<const char*, SDL_Surface*> map;

SDL_Surface* get_surface(const char* path) {
	auto search = map.find(path);
	if (search != map.end()) {
		std::string msg = "Found surface from \"" + std::string(path) + "\", loading";
		warning(msg.c_str());
		return map[path];
	} else {
		std::string msg = "First instance of surface from \"" + std::string(path) + "\", loading and adding to map";
		warning(msg.c_str());
		SDL_Surface *surface = IMG_Load(path);
		if (!surface) {
			sdl_error("resources.cpp >");
		}
		map.insert(std::make_pair(path, surface));

		return surface;
	}
}

void remove_surface(const char* path) {
	auto search = map.find(path);
	if (search != map.end()) {
		message("Removing image from map");
		map.erase(search);
	}
}
