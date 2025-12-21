#ifndef TEXT_H
#define TEXT_H

#include <SDL2/SDL.h>

#include <string>
#include <cstring>
#include <cstdlib>

void init_ttf();
void generate_text(SDL_Renderer* renderer, const char* s, TTF_Font* font, int x, int y, int scale, SDL_Color fore);
void render_text(SDL_Renderer* renderer, const char* s, TTF_Font* font, int x, int y, int scale, SDL_Color fore);
void close_ttf();

#endif
