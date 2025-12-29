#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "include/colors.h"
#include "include/fps.h"
#include "../ui/include/text.h"

Uint32 delta_time;

Uint32 calculate_time(Uint64 start) {
	return ((Uint32)(SDL_GetTicks() - start));
}

void cap (Uint64 start, int max, int show, SDL_Renderer* renderer, TTF_Font* font) {
	delta_time = calculate_time(start);
	if ((1000 / max) > (SDL_GetTicks() - start)) {
		SDL_Delay((1000 / max) - (SDL_GetTicks() - start));
	}
	if (show > 0) {
		const char* fps = (std::to_string((int)(1.f / ((float)(SDL_GetTicks() - start) / 1000.0f)))).c_str();
		render_text(renderer, fps, font, 0, 0, 20, C_GREEN);
	}
}
