#ifndef SOLIDS_H
#define SOLIDS_H

#include <SDL2/SDL.h>

#include <cmath>

#include "vector3d.hpp"
#include "../../../core/misc/include/colors.h"

class Cube {
	private:
		SDL_Renderer* renderer;
		Vector3D position;
		int w;
		int h;
		int d;
		float angle = 0;
		SDL_Color color;

		// Projection matrix for orthographic projection
		float projection_matrix [3][3] = {
			{1, 0, 0},
			{0, 1, 0}
		};
		// Rotation matrix for rotating projection
		float rotation_matrix[3][3] = {
			{1 ,0, 0},
			{0, 1, 0},
			{0, 0, 1}
		};
	
	public:

		Cube(SDL_Renderer *c_renderer, const Vector3D& pos, int width, int height, int depth, float a = 0, SDL_Color c_color = C_WHITE) noexcept;
		Cube(const Cube& c) noexcept;
		Cube(Cube&& c) noexcept;

		Cube operator=(const Cube& c) noexcept;
		Cube operator=(Cube&& c) noexcept;

		Vector3D get_pos() const;
		void set_pos(const Vector3D& n_pos);
		int get_width() const;
		int get_height() const;
		int get_depth() const;
		void set_width(int n_w);
		void set_height(int n_h);
		void set_depth(int n_d);
		SDL_Color get_color() const;
		void set_color(const SDL_Color& color);
		SDL_Renderer* get_renderer() const;
		void render();
		void rotate_x(float speed);
		void rotate_y(float speed);
		void rotate_z(float speed);
};

#endif
