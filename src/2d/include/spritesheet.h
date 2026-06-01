#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL2/SDL.h>

#include <vector>

#include "vector2d.hpp"
#include "../../../core/misc/include/colors.h"

class Spritesheet {
	private:
		SDL_Renderer* ss_renderer;
		const char* path;
		SDL_Texture* texture = NULL;
		int frames;
		Vector2D pos;
		int x;
		int y;
		int w;
		int h;
		SDL_Color color;
		std::vector<SDL_Rect> sprite_clips;
	
	public:
		Spritesheet(SDL_Renderer* renderer, const char* n_path, const Vector2D& n_pos, int n_frames, int n_x, int n_y, int n_w, int n_h, SDL_Color n_color = C_WHITE) noexcept;
		~Spritesheet() noexcept;

		Vector2D get_pos() const;
		void set_pos(const Vector2D& n_pos);
		int get_width() const;
		int get_height() const;
		void set_width(int n_w);
		void set_height(int n_h);
		SDL_Color get_color() const;
		void set_color(SDL_Color n_color);
		void render(int frame) const;
};

#endif
