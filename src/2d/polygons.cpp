#include <SDL2/SDL.h>

#include "../../core/misc/include/log.hpp"
#include "include/polygons.h"
#include "include/vector2d.hpp"

void rect(SDL_Renderer* renderer, Vector2D pos, int w, int h, SDL_Color fcolor, bool filled) {
	SDL_Rect rect;
	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = w;
	rect.h = h;
	SDL_SetRenderDrawColor(renderer, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
	if (filled) {
		SDL_RenderFillRect(renderer, &rect);
	}
	SDL_RenderDrawRect(renderer, &rect);

}

void point(SDL_Renderer* renderer, Vector2D pos, SDL_Color fcolor) {
	SDL_SetRenderDrawColor(renderer, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
	SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

void line(SDL_Renderer* renderer, Vector2D pos1, Vector2D pos2, SDL_Color fcolor) {
	SDL_SetRenderDrawColor(renderer, fcolor.r, fcolor.g, fcolor.b, fcolor.a);
	SDL_RenderDrawLine(renderer, pos1.x, pos1.y, pos2.x, pos2.y);
}
