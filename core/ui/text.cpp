#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

#include "../../platform/linux/vars.hpp"
#include "../misc/include/error.hpp"
#include "../misc/include/colors.h"
#include "../misc/include/split.hpp"
#include "include/text.h"
#include "include/font_paths.hpp"

void init_ttf() {
	if (TTF_Init() < 0) {
		error("font.cpp > Couldn't start SDL_TTF");
	}
	TTF_Font *test_f = TTF_OpenFont(roboto_path, 10);
	if (!test_f) {
		std::string msg_s = "font.cpp > Couldn't load font from \"" + std::string(roboto_path) + "\"";
		const char* msg = msg_s.c_str();
		error(msg);
	}
	success("Dummy font loaded, unloading now...");
	TTF_CloseFont(test_f);
	test_f = NULL;
	success("Dummy font unloaded");
}

void generate_text(SDL_Renderer* renderer, const char* s, TTF_Font* font, int x, int y, int scale, SDL_Color fore) {
	TTF_SetFontSize(font, scale);
	SDL_Surface *surface = TTF_RenderUTF8_Blended(font, s, fore);
	if (!surface) {
		error("text.cpp > Couldn't create surface for text");
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	// Use rectangle to display text inside
	SDL_Rect rect;
	TTF_SizeText(font, s, &rect.w, &rect.h);
	rect.x = x;
	rect.y = y;
	SDL_FreeSurface(surface);
	surface = NULL;
	SDL_RenderCopy(renderer, texture, NULL, &rect);

	SDL_DestroyTexture(texture);
	texture= NULL;
}

void render_text(SDL_Renderer* renderer, const char* s, TTF_Font *font, int x, int y, int scale, SDL_Color fore) {
	TTF_SetFontSize(font, scale);
	// Maximum lenght of a string inside a window is determined by k * (W_W / scale), where k = medium character's width, W_W = window's width, scale = size of individual character
	size_t max_len = floor(2.2 * (W_W / scale));
	auto lines = split(s, max_len);
	int offset = 0;
	for (const char* line : lines) {
		generate_text(renderer, line, font, x, y - offset, scale, fore);
		offset -= scale;
	}
	free_chunks(lines);
}

void close_ttf() {
	TTF_Quit();
	success("Closed TTF");
}
