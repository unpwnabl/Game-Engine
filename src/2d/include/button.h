#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "vector2d.hpp"
#include "image.h"
#include "../../misc/include/gameobj.h"
#include "../../../core/misc/include/colors.h"

class Button : public GameObject {
	private:
		SDL_Renderer* b_renderer;
	public:
		const char* text;
		Vector2D position;
		int w;
		int h;
		bool is_clicked = false;

		Button(SDL_Renderer* renderer, const char* txt, Vector2D pos, int width, int height, Image image);
		~Button();

		void render(TTF_Font* font, int scale = 10, SDL_Color color = C_WHITE) const;
};

#endif
