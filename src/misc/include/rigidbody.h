#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../../2d/include/vector2d.hpp"

class GameObject;

class Rigidbody {
	private:
		double mass;
		double drag;
		GameObject* go;
	public:
		Rigidbody();
		Rigidbody(GameObject* n_go, double n_mass = 0.0, double n_drag = 0.0) noexcept;
		Rigidbody(const Rigidbody& rb) noexcept;
		~Rigidbody() noexcept;

		void set_mass(double n_m);
		void set_drag(double n_d);
		const double get_mass() const;
		const double get_drag() const;
		void add_force(const Vector2D& f);
		void accelerate(const Vector2D& a);
		void impulse(const Vector2D& i);
		void move(const Vector2D& n_pos);
};

bool constraint(GameObject* n_go, const Vector2D& max, const Vector2D& min);

#endif
