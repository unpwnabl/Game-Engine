#ifndef IMAGE_H
#define IMAGE_H

#include <SDL2/SDL.h>

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
		Image(SDL_Renderer *renderer, const char* image_path, int width = 0, int height = 0);

		void set_color(SDL_Color color) const;
		void traslate(int nx, int ny);
		void rotate(double theta);
		void scale(double factor);
		void reflect();

		void render(int x_pos = 0, int y_pos = 0);

		~Image();
};

#endif
