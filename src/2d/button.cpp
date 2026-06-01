#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <string>

#include "include/button.h"
#include "../../core/ui/include/text.h"
#include "../../core/misc/include/mouse.h"
#include "../../core/misc/include/log.hpp"
#include "include/vector2d.hpp"
#include "include/image.h"
#include "../misc/include/gameobj.h"

Button::Button(const char* txt, const Vector2D& pos, int width, int height, const Image& image) noexcept : GameObject("Button", pos, width, height, image), text(txt), position(pos), w(width), h(height) { }

Button::~Button() noexcept {
	text = "";
}

Vector2D Button::get_pos() const {
	return position;
}

void Button::set_pos(const Vector2D& n_pos) {
	position = n_pos;
	get_image().set_pos(position);
}

int Button::get_width() const {
	return w;
}

int Button::get_height() const {
	return h;
}

void Button::set_width(int n_w) {
	w = n_w;
	get_image().set_width(w);
}

void Button::set_height(int n_h) {
	h = n_h;
	get_image().set_height(h);
}

bool Button::clicked() const {
	if (left_click.x > position.x && left_click.x < position.x + w && left_click.y < position.y && left_click.y > position.y + h && is_clicked) {
		std::cout << "Pressed" << std::endl;	
		return true;
	}
	return false;
}

void Button::render(TTF_Font* font, int scale, SDL_Color color) const {
	// Render text in the middle of the button	
	get_image().render();
	render_text(get_image().get_renderer(), text, font, position.x, position.y, scale, color);
}
