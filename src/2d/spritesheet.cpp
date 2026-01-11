#include <SDL2/SDL.h>

#include <vector>
#include <string>

#include "include/spritesheet.h"
#include "include/vector2d.hpp"
#include "../misc/include/resources.h"
#include "../../core/misc/include/log.hpp"
#include "../../core/misc/include/colors.h"

// Thanks to https://lazyfoo.net/tutorials/SDL/14_animated_sprites_and_vsync/index.php for the explanation (and image)

Spritesheet::Spritesheet(SDL_Renderer* renderer, const char* n_path, const Vector2D& n_pos, int n_frames, int n_x, int n_y, int n_w, int n_h, SDL_Color n_color) noexcept : ss_renderer(renderer), path(n_path), pos(n_pos), frames(n_frames), x(n_x), y(n_y), w(n_w), h(n_h), color(n_color) {
	texture = SDL_CreateTextureFromSurface(ss_renderer, get_surface(path));
	
	for (int i = 0; i <= frames; i++) {
		SDL_Rect sprite;
		sprite.x = i * x;
		sprite.y = (i % frames) * y;
		sprite.w = w;
		sprite.h = h;
		sprite_clips.insert(sprite_clips.begin() + i, sprite);
	}
	SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
}

Spritesheet::~Spritesheet() noexcept {
	if (texture) {
		remove_surface(path);
		SDL_DestroyTexture(texture);
		texture = NULL;
		std::string msg = "Removed spritesheet \"" + std::string(path) + "\" from memory";
		message(msg.c_str());
	} else {
		warning("No spritesheet found, already deleted?");
	}
}

Vector2D Spritesheet::get_pos() const {
	return pos;
}

void Spritesheet::set_pos(const Vector2D&n_pos) {
	pos = n_pos;
}

int Spritesheet::get_width() const {
	return w;
}

int Spritesheet::get_height() const {
	return h;
}

void Spritesheet::set_width(int n_w) {
	w = n_w;
}

void Spritesheet::set_height(int n_h) {
	h = n_h;
}

SDL_Color Spritesheet::get_color() const {
	return color;
} 

void Spritesheet::set_color(SDL_Color n_color) {
	color = n_color;
} 

void Spritesheet::render(int frame) const {
	SDL_Rect clip = { (int)pos.x, (int)pos.y, sprite_clips[frame].w, sprite_clips[frame].h };
	SDL_RenderCopy(ss_renderer, texture, &sprite_clips[frame], &clip);
}
