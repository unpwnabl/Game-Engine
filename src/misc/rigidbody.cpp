#include <iostream>

#include "include/rigidbody.h"
#include "include/gameobj.h"
#include "../2d/include/vector2d.hpp"
#include "../../../core/misc/include/log.hpp"
#include "../../../core/misc/include/fps.h"
#include "../../../core/misc/include/interpolation.hpp"
#include "../../../platform/linux/vars.hpp"

Rigidbody::Rigidbody() { }

Rigidbody::Rigidbody(GameObject* n_go, double n_mass, double n_drag) noexcept : go(n_go), mass(n_mass), drag(n_drag) { }
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
	// QUESTION: Why are we subtracting vectors when we should be adding them? (ADD_FORCE yk)
	// ANSWER: Because apparently the GameObject sum with positive vector is going down, while the GameObject sum with negative vector is going up
	// ¯\_(ツ)_/¯
	go->set_pos(go->get_pos() - Vector2D((f.x * delta_time) / mass, (f.y * delta_time) / mass));
}

void Rigidbody::accelerate(const Vector2D& a) {
	go->set_pos(go->get_pos() + Vector2D(a.x * delta_time, a.y * delta_time));
}

void Rigidbody::impulse(const Vector2D& i) {
	go->set_pos(go->get_pos() + Vector2D(i.x / mass, i.y / mass));
}

void Rigidbody::move(const Vector2D& n_pos) {
	go->set_pos(go->get_pos() + Vector2D(lerp(go->get_pos().x, n_pos.x, 0.1), lerp(go->get_pos().y, n_pos.y, 0.1)));
}

void Rigidbody::constrain() {
	if (go->get_pos() >= Vector2D(W_W, W_H) || go->get_pos() < Vector2D(0, 0)) {
		go->set_pos(go->get_pos());
	}
}
