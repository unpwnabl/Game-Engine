#ifndef RESOURCES_H
#define RESOURCES_H

#include <SDL2/SDL.h>

#include <unordered_map>

SDL_Texture* get_texture(SDL_Renderer* renderer, const char* path);
void remove_texture(const char* path);

#endif
