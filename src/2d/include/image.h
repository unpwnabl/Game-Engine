#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>

#include "../../../core/misc/include/colors.h"

void init_img(int flags);

class Image {
	private:
		const char* path;
		SDL_Texture* texture = NULL;
		SDL_Renderer* i_renderer;
		SDL_Rect rect;
	public:
		int x;
		int y;
		int w;
		int h;
		SDL_Point center;
		SDL_Color color;

		Image(SDL_Renderer *renderer, const char* image_path, int x_pos = 0, int y_pos = 0, int width = 0, int height = 0, SDL_Color i_color = C_WHITE);
		Image(const Image& img);
		~Image();

		Image& operator=(const Image& img);

		void set_color(SDL_Color color);
		void render() const;
};

void close_img();

#endif
