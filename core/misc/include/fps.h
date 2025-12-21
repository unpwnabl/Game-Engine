#ifndef FPS_H
#define FPS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void cap(Uint64 start, int max, int show = 0, SDL_Renderer *renderer = NULL, TTF_Font *font = NULL);

#endif
