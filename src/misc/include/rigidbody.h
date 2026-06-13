#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../../2d/include/vector2d.hpp"

class GameObject;

class Rigidbody {
	private:
		double mass;
		double drag;
		GameObject* go;
		double g;
		double weight;
		Vector2D friction;
	public:
		Rigidbody();
		Rigidbody(GameObject* n_go, double n_mass = 0.0, double n_drag = 0.0) noexcept;
		Rigidbody(const Rigidbody& rb) noexcept;
		~Rigidbody() noexcept;

		void set_mass(double n_m);
		void set_drag(double n_d);
		const double get_mass() const;
		const double get_drag() const;
		void set_gravity(double g);
		const double get_gravity() const;

		void fall();
		void translate(const Vector2D& trans);
		void move_to(const Vector2D& n_pos);

		bool is_box_colliding(const GameObject& n_go);
		bool is_line_colliding(const Vector2D& p1, const Vector2D& p2);
};

#endif
