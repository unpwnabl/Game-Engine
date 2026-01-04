#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

#include "include/button.h"
#include "../../core/ui/include/text.h"
#include "../../core/misc/include/log.hpp"
#include "include/vector2d.hpp"
#include "include/image.h"
#include "../misc/include/gameobj.h"

Button::Button(SDL_Renderer* renderer, const char* txt, Vector2D pos, int width, int height, Image image) : GameObject("Button", pos.x, pos.y, width, height, renderer, image), b_renderer(renderer), text(txt), position(pos), w(width), h(height) {
	std::cout << "Button(" << x << ", " << y << ")" << std::endl;
};

Button::~Button() {
	text = "";
	b_renderer = NULL;
	img.~Image();
	position.~Vector2D();
}

void Button::render(TTF_Font* font, int scale, SDL_Color color) const {
	// Render text in the middle of the button	
	img.render();
	int len_x = position.x + img.x / 2 - (2.2 * (int)std::strlen(text));
	int len_y = position.y - img.y + scale / 2;
	render_text(b_renderer, text, font, len_x, len_y, scale, color);
}
