#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>

#include "vector2d.hpp"
#include "../../../core/misc/include/colors.h"

void init_img(int flags);

class Image {
	private:
		const char* path;
		SDL_Texture* texture = NULL;
		SDL_Renderer* i_renderer;
		SDL_Rect rect;
		Vector2D position;
		int w;
		int h;
		SDL_Point center;
		SDL_Color color;
	
	public:

		Image(SDL_Renderer *renderer, const char* image_path, int x_pos = 0, int y_pos = 0, int width = 0, int height = 0, SDL_Color i_color = C_WHITE);
		Image(const Image& img);
		~Image();
	
		Vector2D get_pos() const;
		void set_pos(const Vector2D& n_pos);
		int get_width() const;
		int get_height() const;
		void set_width(int n_w);
		void set_height(int n_h);
		SDL_Color get_color() const;
		void set_color(const SDL_Color& color);
		void render() const;
};

void close_img();

#endif
