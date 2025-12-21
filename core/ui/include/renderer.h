#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

void create_renderer(SDL_Window* window, SDL_Renderer*& renderer);
void render_rect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);
void renderer_update(SDL_Renderer* renderer);
void renderer_clear(SDL_Renderer* renderer);
void destroy_renderer(SDL_Renderer*& renderer);

#endif
