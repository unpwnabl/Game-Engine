#include <iostream>

#include "include/rigidbody.h"
#include "include/gameobj.h"
#include "../2d/include/vector2d.hpp"
#include "../../../core/misc/include/log.hpp"
#include "../../../core/misc/include/fps.h"
#include "../../../platform/linux/vars.hpp"

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

void Rigidbody::fall() {
	translate(Vector2D(0, -g));
}

void Rigidbody::translate(const Vector2D& trans) {
	// Framerate-dependent movement
	go->set_pos(go->get_pos() + trans);
}

void Rigidbody::move_to(const Vector2D& n_pos) {
	go->set_pos(n_pos);
}

bool Rigidbody::is_box_colliding(const GameObject& n_go) {
	// GameObject go
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
	// GameObject n_go
	// Vector2D(x,y)    w	Vector2D(x+w,y)
	//		+-------+
	//		|	|
	//		|	|
	//	      h |	|
	//		|	|
	//		|	|
	//		+-------+
	// Vector2D(x,y+h)	Vector2D(x+w,y+h)
	
	Vector2D pos = go->get_pos();

	// Left and right
	if (	pos.x < n_go.get_pos().x + n_go.get_width() &&
		pos.x + go->get_width() > n_go.get_pos().x &&
		pos.y < n_go.get_pos().y + n_go.get_height() &&
		pos.y + go->get_height() > n_go.get_pos().y) {
		return true;
	}
	return false;
}

// Thanks to Jeffrey Thompson for the functions and the explanations
// See more here: www.jeffreythompson.org/collision-detection/line-rect.php

bool line_line_colliding(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
		return true;
	}
	return false;
}

bool Rigidbody::is_line_colliding(const Vector2D& p1, const Vector2D& p2) {
	// GameObject go
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
	// Line
	// Vector2D(p1.x,p1.y)	    		Vector2D(p2.x,p2.y)
	//		+-----------------------+
	
	Vector2D pos = go->get_pos();

	// We simplify the collision checking for line-line intersection between an effective line and the lines that make up the box collider
	if (	line_line_colliding(p1.x, p1.y, p2.x, p2.y, pos.x, pos.y, pos.x, pos.y + go->get_width()) ||
		line_line_colliding(p1.x, p1.y, p2.x, p2.y, pos.x + go->get_width(), pos.y, pos.x + go->get_width(), pos.y + go->get_height()) ||
		line_line_colliding(p1.x, p1.y, p2.x, p2.y, pos.x, pos.y, pos.x + go->get_width(), pos.y) ||
		line_line_colliding(p1.x, p1.y, p2.x, p2.y, pos.x, pos.y + go->get_height(), pos.x + go->get_width(), pos.y + go->get_height())) {
		return true;
	}
	return false;
}
