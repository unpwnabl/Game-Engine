#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <SDL2/SDL.h>

#include "../../2d/include/vector2d.hpp"
#include "../../2d/include/image.h"
#include "../../../core/misc/include/colors.h"

class GameObject {
	private:
		const char* name;
		Vector2D position;
		int w;
		int h;
		Image img;

	public:
		GameObject(const char* id, Vector2D pos, int width, int height, Image& image);
		GameObject(const GameObject& go);
		~GameObject();

		const char* get_name() const;
		void set_name(const char* n_n);
		Vector2D get_pos() const;
		void set_pos(const Vector2D& n_pos);
		int get_width() const;
		int get_height() const;
		void set_width(int n_w);
		void set_height(int n_h);
		Image get_image() const;
		void set_image(const Image& image);
		void render() const;
};

#endif
