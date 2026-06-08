#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "../../2d/include/vector2d.hpp"

class GameObject;

bool constrain(GameObject* n_go, const Vector2D& max, const Vector2D& min);

extern int UP;
extern int DOWN;
extern int LEFT;
extern int RIGHT;

class Rigidbody {
	private:
		double mass;
		double drag;
		GameObject* go;
		double g;
		double weight;
		Vector2D friction;
		float delta;
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
		void set_delta(float speed);
		const float get_delta() const;
		void fall();
		void move(float speed, int direction);
		void move_to(const Vector2D& n_pos);
};

#endif
