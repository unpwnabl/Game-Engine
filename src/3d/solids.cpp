#include <SDL2/SDL.h>

#include <cmath>

#include "include/solids.h"
#include "include/vector3d.hpp"
#include "../2d/include/polygons.h"
#include "../2d/include/vector2d.hpp"
#include "../../core/misc/include/matrix.hpp"
#include "../../core/misc/include/colors.h"
#include "../../core/misc/include/log.hpp"


Cube::Cube(SDL_Renderer* c_renderer, const Vector3D& pos ,int width, int height, int depth, float a, SDL_Color c_color) noexcept : renderer(c_renderer), w(width), h(height), d(depth), angle(a), color(c_color), position(pos) { };

Cube::Cube(const Cube& c) noexcept : renderer(c.renderer), position(c.position), w(c.w), h(c.h), d(c.d), angle(c.angle), color(c.color) 
{
	message("Copied cube");
}

Cube::Cube(Cube&& c) noexcept : renderer(c.renderer), position(c.position), w(c.w), h(c.h), d(c.d), angle(c.angle), color(c.color) {
	message("Moved cube");
}

Cube Cube::operator=(const Cube& c) noexcept {
	if (this != &c) {
		renderer = c.renderer;
		position = c.position;
		w = c.w;
		h = c.h;
		d = c.d;
		angle = c.angle;
		color = c.color;
	}
	return *this;
}

Cube Cube::operator=(Cube&& c) noexcept {
	if (this != &c) {
		renderer = c.renderer;
		position = c.position;
		w = c.w;
		h = c.h;
		d = c.d;
		color = c.color;
		angle = c.angle;
	}
	return *this;
}


Vector3D Cube::get_pos() const {
	return position;
}

void Cube::set_pos(const Vector3D& n_pos) {
	position = n_pos;
}

int Cube::get_width() const {
	return w;
}

int Cube::get_height() const {
	return h;
}

int Cube::get_depth() const {
	return d;
}

void Cube::set_width(int n_w) {
	w = n_w;
}

void Cube::set_height(int n_h) {
	h = n_h;
}

void Cube::set_depth(int n_d) {
	d = n_d;
}


SDL_Color Cube::get_color() const {
	return color;
}

void Cube::set_color(const SDL_Color& n_c) {
	color = n_c;
}

SDL_Renderer* Cube::get_renderer() const {
	return renderer;
}

// Thanks to Daniel Shiffman for the functions and the explanations
// See more here: https://www.youtube.com/watch?v=p4Iz0XJY-Qk

void Cube::render() {
	int n_points = 8;

	auto points = new Vector3D[n_points];

	//			     +------+  <- (x + width, y, z - depth)
	//			   .'|    .'|
	//	 (x, y, z)->	 +---+--+'  |
	//			 |   |  |   |
	//			 |   +--+---+
	//			 | .'   | .'
	//			 +------+'

	points[0] = Vector3D(position.x, position.y, position.z); 
	points[1] = Vector3D(position.x + w, position.y, position.z);
	points[2] = Vector3D(position.x + w, position.y - h, position.z);
	points[3] = Vector3D(position.x, position.y - h, position.z);

	points[4] = Vector3D(position.x, position.y, position.z - d);
	points[5] = Vector3D(position.x + w, position.y, position.z - d);
	points[6] = Vector3D(position.x + w, position.y - h, position.z - d);
	points[7] = Vector3D(position.x, position.y - h, position.z - d);

	auto projected_cube = new Vector3D[n_points];

	// Render points
	for (int i = 0; i < n_points; i++) {
		float* rotated_matrix = matrix_mult(
				(float*)rotation_matrix, 
				3, 3, 
				(float*)vect3d_to_matrix(points[i]), 
				3, 1);
		Vector3D rotated_v = matrix_to_vect3d((float*)rotated_matrix, 3, 1);
		
		float* projected_matrix = matrix_mult((float*)projection_matrix, 2, 3, (float*)vect3d_to_matrix(rotated_v), 3, 1);
		Vector3D final = matrix_to_vect3d((float*)projected_matrix, 2, 1);
		projected_cube[i] = final;
		// point(renderer, Vector2D(final.x, final.y), color);
	}

	// Render edges
	for (int i = 0; i < 4; i++) {
		connect(renderer, 
				Vector2D(projected_cube[i].x, projected_cube[i].y), 
				Vector2D(projected_cube[((i + 1) % 4)].x, projected_cube[((i + 1) % 4)].y)
		);
		connect(renderer, 
				Vector2D(projected_cube[i + 4].x, projected_cube[i + 4].y), 
				Vector2D(projected_cube[(((i + 1) % 4) + 4)].x, projected_cube[(((i + 1) % 4) + 4)].y)
		);
		connect(renderer, 
				Vector2D(projected_cube[i].x, projected_cube[i].y), 
				Vector2D(projected_cube[(i + 4)].x, projected_cube[(i + 4)].y)
		);
	}

}

void Cube::rotate_x(float speed) {
	if (angle >= 360) {
		angle = 0;
	}
	angle += speed;
	// rotation_matrix = {
	// 	{1, 0, 0},
	//	{0, cos(angle), -sin(angle)},
	//	{0, sin(angle), cos(angle)}
	// };
	rotation_matrix[0][0] = 1;
	rotation_matrix[0][1] = 0;
	rotation_matrix[0][2] = 0;
	rotation_matrix[1][0] = 0;
	rotation_matrix[1][1] = cos(angle);
	rotation_matrix[1][2] = -sin(angle);
	rotation_matrix[2][0] = 0;
	rotation_matrix[2][1] = sin(angle);
	rotation_matrix[2][2] = cos(angle);
}

void Cube::rotate_y(float speed) {
	if (angle >= 360) {
		angle = 0;
	}
	angle += speed;
	// rotation_matrix = {
	// 	{cos(angle), 0, -sin(angle)},
	//	{0, 1, 0},
	//	{sin(angle), 0, cos(angle)}
	// };
	rotation_matrix[0][0] = cos(angle);
	rotation_matrix[0][1] = 0;
	rotation_matrix[0][2] = -sin(angle);
	rotation_matrix[1][0] = 0;
	rotation_matrix[1][1] = 1;
	rotation_matrix[1][2] = 0;
	rotation_matrix[2][0] = sin(angle);
	rotation_matrix[2][1] = 0;
	rotation_matrix[2][2] = cos(angle);
}

void Cube::rotate_z(float speed) {
	if (angle >= 360) {
		angle = 0;
	}
	angle += speed;
	// rotation_matrix = {
	// 	{cos(angle), -sin(angle), 0},
	//	{sin(angle), cos(angle), 0},
	//	{0, 0, 1}
	// };
	rotation_matrix[0][0] = cos(angle);
	rotation_matrix[0][1] = -sin(angle);
	rotation_matrix[0][2] = 0;
	rotation_matrix[1][0] = sin(angle);
	rotation_matrix[1][1] = cos(angle);
	rotation_matrix[1][2] = 0;
	rotation_matrix[2][0] = 0;
	rotation_matrix[2][1] = 0;
	rotation_matrix[2][2] = 1;
}
