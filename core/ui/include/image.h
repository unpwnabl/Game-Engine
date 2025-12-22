#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>

class Image {
	private:
		const char* path;
		SDL_Texture *texture = NULL;
		SDL_Rect rect;
	public:
		int x;
		int y;
		int w;
		int h;
		Image();
		Image(SDL_Renderer *renderer, const char* image_path, int width = 0, int height = 0);	

		void render(SDL_Renderer *renderer, int x_pos = 0, int y_pos = 0);

		~Image();
};

#endif
