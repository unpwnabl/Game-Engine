#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL.h>

extern bool key_is_pressed;
extern SDL_Scancode scancode;
extern const char* key;

void update_key(SDL_Event& event);

#endif
