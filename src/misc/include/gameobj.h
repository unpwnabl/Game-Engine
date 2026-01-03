#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <SDL2/SDL.h>

#include "../../2d/include/image.h"
#include "../../../core/misc/include/colors.h"

class GameObject {
	private:
		SDL_Renderer* go_renderer;
	public:
		const char* name;
		int x;
		int y;
		int w;
		int h;
		Image img;
		
		GameObject();
		GameObject(const char* id, int x_pos, int y_pos, int width, int height, SDL_Renderer* renderer, Image& image);
		~GameObject();

		void render();
};

#endif
