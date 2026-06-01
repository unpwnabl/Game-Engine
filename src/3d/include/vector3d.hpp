#ifndef VECTOR3D_HPP
#define VECTOR3D_HPP

#include <iostream>

#include "../../2d/include/vector2d.hpp"

class Vector2D;

class Vector3D {
	public:
		double x;
		double y;
		double z;

		Vector3D();
		Vector3D(double x_pos, double y_pos, double z_pos);
		
		Vector3D operator+(const Vector3D& v3d) const;
		Vector3D operator-(const Vector3D& v3d) const;
		Vector3D operator*(const double s) const;
		bool operator==(const Vector3D& v3d) const;
		bool operator!=(const Vector3D& v3d) const;
		bool operator<(const Vector3D& v3d) const;
		bool operator>(const Vector3D& v3d) const;
		friend std::ostream& operator<<(std::ostream& os, const Vector3D& v3d);
		
		double magnitude() const;
};

Vector3D to_vect3d(const Vector2D& v2d);
// Dot product, returns a scalar
double dot3d(const Vector3D& v3d1, const Vector3D& v3d2);
// Cross product, returns a vector
Vector3D cross3d(const Vector3D& v3d1, const Vector3D& v3d2);
// Angle between two vectors
double angle3d(const Vector3D& v3d1, const Vector3D& v3d2);

#endif

