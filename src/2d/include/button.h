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
		SDL_Renderer* b_renderer = NULL;
		const char* text;
		Vector2D position;
		int w;
		int h;
	
	public:

		Button(const char* txt, Vector2D pos, int width, int height, Image image);
		~Button();

		void set_renderer(SDL_Renderer* renderer);
		Vector2D get_pos() const;
		void set_pos(const Vector2D& n_pos);
		int get_width() const;
		int get_height() const;
		void set_width(int n_w);
		void set_height(int n_h);
		bool clicked() const;
		void render(TTF_Font* font, int scale = 10, SDL_Color color = C_WHITE) const;
};

#endif
