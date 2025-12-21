#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string>

#include "include/colors.h"
#include "include/fps.h"
#include "../ui/include/text.h"

void cap(Uint64 start, int max, int show, SDL_Renderer* renderer, TTF_Font* font) {
	if ((1000 / max) > (SDL_GetTicks() - start)) {
		SDL_Delay((1000 / max) - (SDL_GetTicks() - start));
	}
	if (show > 0) {
		const char* fps = (std::to_string((int)(1.f / ((float)(SDL_GetTicks() - start) / 1000.0f)))).c_str();
		render_text(renderer, fps, font, 0, 0, 20, C_GREEN);
	}
}
