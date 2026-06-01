#ifndef FPS_H
#define FPS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern float delta_time;

float calculate_time(Uint64 start);
void cap(Uint64 start, int max, int show = 0, SDL_Renderer *renderer = NULL, TTF_Font *font = NULL);

#endif
