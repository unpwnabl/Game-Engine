#include <SDL2/SDL.h>

#include "include/keyboard.h"
#include "include/log.hpp"

bool key_is_pressed;
SDL_Scancode scancode;
const char* keycode;

const char* key;

void update_key(SDL_Event& event) {
	if (event.type == SDL_KEYDOWN) {
		key_is_pressed = true;
		scancode = event.key.keysym.scancode;
		keycode = SDL_GetScancodeName(scancode);
		if (keycode != "") {
			key = keycode;
		} else {
			error("keyboard.cpp > Couldn't understand scancode of key");
		}
	} else if (event.type == SDL_KEYUP) {
		key_is_pressed = false;
		scancode = SDL_SCANCODE_UNKNOWN;
		key = "";
	}
}
