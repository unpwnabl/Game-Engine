#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

// Minimum sizes
#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 540

void create_window(SDL_Window*& window, const char* title, int x = SDL_WINDOWPOS_CENTERED, int y = SDL_WINDOWPOS_CENTERED, int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);

void destroy_window(SDL_Window*& window);

#endif
