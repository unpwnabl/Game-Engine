#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>

void init_img(int flags);

class Image {
	private:
		const char* path;
		SDL_Texture *texture = NULL;
		SDL_Renderer *i_renderer;
		SDL_Rect rect;
	public:
		int x;
		int y;
		int w;
		int h;
		SDL_Point center;
		Image();
		Image(SDL_Renderer *renderer, const char* image_path, int x_pos = 0, int y_pos = 0, int width = 0, int height = 0);

		void set_color(SDL_Color color) const;
	
		void render();

		~Image();
};

void close_img();

#endif
