#ifndef RESOURCES_H
#define RESOURCES_H

#include <SDL2/SDL.h>

#include <unordered_map>

SDL_Surface* get_surface(const char* path);
void remove_surface(const char* path);

#endif
