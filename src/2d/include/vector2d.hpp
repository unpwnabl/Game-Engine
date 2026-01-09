#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <iostream>

#include "../../3d/include/vector3d.hpp"

class Vector3D;

class Vector2D {
	public:
		double x;
		double y;
		
		Vector2D();
		Vector2D(double x_pos, double y_pos);
		
		Vector2D operator+(const Vector2D& v2d) const;
		Vector2D operator-(const Vector2D& v2d) const;
		Vector2D operator*(const double s) const;
		bool operator==(const Vector2D& v2d) const;
		bool operator!=(const Vector2D& v2d) const;
		bool operator<(const Vector2D& v2d) const;
		bool operator>(const Vector2D& v2d) const;
		bool operator<=(const Vector2D& v2d) const;
		bool operator>=(const Vector2D& v2d) const;
		friend std::ostream& operator<<(std::ostream& os, const Vector2D& v2d);
		
		double magnitude() const;
};

Vector2D to_vect2d(const Vector3D& v3d);
// Dot product, returns a scalar
double dot2d(const Vector2D& v2d1, const Vector2D& v2d2);
// Angle between two vectors
double angle2d(const Vector2D& v2d1, const Vector2D& v2d2);

#endif
