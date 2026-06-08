#include <iostream>

#include "include/rigidbody.h"
#include "include/gameobj.h"
#include "../2d/include/vector2d.hpp"
#include "../../../core/misc/include/log.hpp"
#include "../../../core/misc/include/fps.h"
#include "../../../platform/linux/vars.hpp"

bool constrain(GameObject* n_go, const Vector2D& max, const Vector2D& min) {
	// GameObject
	// Vector2D(x,y)    w	Vector2D(x+w,y)
	//		+-------+
	//		|	|
	//		|	|
	//	      h |	|
	//		|	|
	//		|	|
	//		+-------+
	// Vector2D(x,y+h)	Vector2D(x+w,y+h)
	//
	// Screen
	// Vector2D(min.x,min.y)	    w		Vector2D(max.x,min.y)
	//		  (0,0)	+-----------------------+
	//			|			|
	//			|			|
	//		      h |			|
	//			|			|
	//			|			|
	//			+-----------------------+ (W_W, W_H)
	// Vector2D(min.x,max.y)			Vector2D(max.x,max.y)
	
	Vector2D pos = n_go->get_pos();

	// Left and right
	if (pos.x - n_go->rb->get_delta() <= min.x) {
		n_go->set_pos(Vector2D(min.x, pos.y));
		n_go->rb->set_delta(0);
		return true;
	} else if (pos.x + n_go->get_width() + n_go->rb->get_delta() >= max.x ) {
		n_go->set_pos(Vector2D(max.x - n_go->get_width(), pos.y));
		n_go->rb->set_delta(0);
		return true;
	}
	// Top and bottom
	if (pos.y - n_go->rb->get_delta() <= min.y) {
		n_go->set_pos(Vector2D(pos.x, min.y));
		n_go->rb->set_delta(0);
		return true;
	} else if (pos.y + n_go->get_height() + n_go->rb->get_delta() >= max.y) {
		n_go->set_pos(Vector2D(pos.x, max.y - n_go->get_height()));
		n_go->rb->set_delta(0);
		// Also remove gravity
		n_go->rb->set_gravity(0);
		return true;
	}
	// Corners
	if (Vector2D(pos.x, pos.y + n_go->get_height()) <= min) {
		// Top-left corner
		n_go->set_pos(Vector2D(min.x, min.y - n_go->get_height()));
		n_go->rb->set_delta(0);
	} else if (Vector2D(pos.x + n_go->get_width(), pos.y) >= Vector2D(max.x, min.y)) {
		// Top-right corner
		n_go->set_pos(Vector2D(max.x - n_go->get_width(), min.y));
		n_go->rb->set_delta(0);
	} else if (Vector2D(pos.x, pos.y + n_go->get_height()) >= Vector2D(min.x, max.y)) {
		// Bottom-left corner
		n_go->set_pos(Vector2D(min.x, max.y - n_go->get_height()));
		n_go->rb->set_delta(0);
		n_go->rb->set_gravity(0);
	} else if (Vector2D(pos.x + n_go->get_width(), pos.y + n_go->get_height()) >= max) {
		// Bottom-right corner
		n_go->set_pos(Vector2D(max.x - n_go->get_width(), max.y - n_go->get_height()));
		n_go->rb->set_delta(0);
		n_go->rb->set_gravity(0);
	}
	return false;
}

int UP = 1;
int DOWN = 2;
int LEFT = 3;
int RIGHT = 4;

Rigidbody::Rigidbody(GameObject* n_go, double n_mass, double n_drag) noexcept : go(n_go), mass(n_mass), drag(n_drag), g(9.87), weight(mass * g), friction(Vector2D(weight * (-1 * drag), weight * (-1 * drag))) { }
Rigidbody::Rigidbody(const Rigidbody& rb) noexcept : go(rb.go), mass(rb.mass), drag(rb.drag) { }
Rigidbody::~Rigidbody() noexcept { }

void Rigidbody::set_mass(double n_m) {
	mass = n_m;
}

void Rigidbody::set_drag(double n_d) {
	drag = n_d;
}

const double Rigidbody::get_mass() const {
	return mass;
}

const double Rigidbody::get_drag() const {
	return drag;
}

void Rigidbody::set_gravity(double n_g) {
	g = n_g;
}

const double Rigidbody::get_gravity() const {
	return g;
}

void Rigidbody::set_delta(float speed) {
	delta = speed;
}

const float Rigidbody::get_delta() const {
	return delta;
}

void Rigidbody::fall() {
	move(g, DOWN);
}

void Rigidbody::move(float speed, int direction) {
	set_delta(speed);
	// Check end position
	Vector2D end_pos = go->get_pos();
	if (direction == UP) {
		end_pos.y -= delta;
	} else if (direction == DOWN) {
		end_pos.y += delta;
	} else if (direction == LEFT) {
		end_pos.x -= delta;	
	} else if (direction == RIGHT) {
		end_pos.x += delta;
	}
	go->set_pos(end_pos);
	if (constrain(go, Vector2D(W_W, W_H), Vector2D(0, 0))) return;
}

void Rigidbody::move_to(const Vector2D& n_pos) {
	go->set_pos(n_pos);
}
