#include <iostream>

#include "include/rigidbody.h"
#include "include/gameobj.h"
#include "../2d/include/vector2d.hpp"
#include "../../../core/misc/include/log.hpp"
#include "../../../core/misc/include/fps.h"
#include "../../../core/misc/include/interpolation.hpp"
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

void Rigidbody::add_force(const Vector2D& f) {
	if (constraint(go, Vector2D(W_W, W_H), Vector2D(0, 0))) return;
	// QUESTION: Why are we negating vectors when we should be just adding them? (ADD_FORCE yk)
	// ANSWER: Because apparently the position + positive vector is going down, while the position + negative vector is going up
	// Thanks SDL ¯\_(ツ)_/¯
	go->set_pos(go->get_pos() + Vector2D((f.x * delta_time) / mass, -1 * ((f.y * delta_time) / mass)) - friction);
}

void Rigidbody::accelerate(const Vector2D& a) {
	if (constraint(go, Vector2D(W_W, W_H), Vector2D(0, 0))) return;
	go->set_pos(go->get_pos() + Vector2D(a.x * delta_time, a.y * delta_time) - friction);
}

void Rigidbody::set_gravity(double n_g) {
	g = n_g;
}

void Rigidbody::fall() {
	accelerate(Vector2D(0, g));
}

void Rigidbody::impulse(const Vector2D& i) {
	if (constraint(go, Vector2D(W_W, W_H), Vector2D(0, 0))) return;
	go->set_pos(go->get_pos() + Vector2D(i.x / mass, i.y / mass) - friction);
}

void Rigidbody::move(const Vector2D& n_pos) {
	if (constraint(go, Vector2D(W_W, W_H), Vector2D(0, 0))) return;
	go->set_pos(go->get_pos() + Vector2D(lerp(go->get_pos().x, n_pos.x, 0.1), lerp(go->get_pos().y, n_pos.y, 0.1)) - friction);
}

bool constraint(GameObject* n_go, const Vector2D& max, const Vector2D& min) {
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
	//			+-----------------------+
	//			|			|
	//			|			|
	//		      h |			|
	//			|			|
	//			|			|
	//			+-----------------------+
	// Vector2D(min.x,max.y)			Vector2D(max.x,max.y)
	
	if (	n_go->get_pos() <= min || 
		n_go->get_pos().y <= min.y || 
		Vector2D(n_go->get_pos().x + n_go->get_width(), n_go->get_pos().y) >= Vector2D(max.x, min.y) || 
		Vector2D(n_go->get_pos().x, n_go->get_pos().y + n_go->get_height()) >= Vector2D(min.x, max.y) ||
		Vector2D(n_go->get_pos().x + n_go->get_width(), n_go->get_pos().y + n_go->get_height()) >= max) {
		return true;
	}
	return false;
}
