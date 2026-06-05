#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "include/colors.h"
#include "include/fps.h"
#include "../ui/include/text.h"

float delta_time;
int delay = 1000;

float calculate_time(Uint64 start) {
	return (float)(SDL_GetTicks() - start);
}

void cap (Uint64 start, int max, bool show, SDL_Renderer* renderer, TTF_Font* font) {
	delta_time = calculate_time(start);
	if ((delay / max) > (SDL_GetTicks() - start)) {
		SDL_Delay((delay / max) - (SDL_GetTicks() - start));
	}
	if (show == true) {
		const char* fps = (std::to_string((int)(1.f / ((float)(SDL_GetTicks() - start) / 1000.0f)))).c_str();
		render_text(renderer, fps, font, 0, 0, 15, C_GREEN);
	}
}
