#include <iostream>
#include <cmath>

#include "../2d/include/vector2d.hpp"
#include "include/vector3d.hpp"

Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) {};

Vector3D::Vector3D(double x_pos, double y_pos, double z_pos) : x(x_pos), y(y_pos), z(z_pos) {};

Vector3D Vector3D::operator+(const Vector3D& v3d) const {
	return Vector3D(x + v3d.x, y + v3d.y, z + v3d.z);
}

Vector3D Vector3D::operator-(const Vector3D& v3d) const {
	return Vector3D(x + (-1.0 * v3d.x), y + (-1.0 * v3d.y), z + (-1.0 * v3d.z));
}

Vector3D Vector3D::operator*(const double s) const {
	return Vector3D(x * s, y * s, z * s);
}

bool Vector3D::operator==(const Vector3D& v3d) const {
	if (x == v3d.x && y == v3d.y && z == v3d.z) {
		return true;
	}
	return false;
}

bool Vector3D::operator!=(const Vector3D& v3d) const {
	if (x != v3d.x || y != v3d.y || z != v3d.z) {
		return true;
	}
	return false;
}

bool Vector3D::operator<(const Vector3D& v3d) const {
	if (x < v3d.x && y < v3d.y && z < v3d.z) {
		return true;
	}
	return false;
}

bool Vector3D::operator>(const Vector3D& v3d) const {
	if (x > v3d.x && y > v3d.y && z > v3d.z) {
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v3d){
	return os << "Vector3D(" << v3d.x << ", " << v3d.y << ", " << v3d.z << ")";
}

double Vector3D::magnitude() const {
	return std::sqrt((x * x) + (y * y) + (z * z));
}

Vector3D to_vect3d(const Vector2D& v2d) {
	return Vector3D(v2d.x, v2d.y, 0.0);
}

double dot3d(const Vector3D& v3d1, const Vector3D& v3d2) {
	// Dot product is x1 * x2 + y1 * y2 + z1 * z2
	return v3d1.x * v3d2.x + v3d1.y * v3d2.y + v3d1.z * v3d2.z;
}

Vector3D cross3d(const Vector3D& v3d1, const Vector3D& v3d2) {
	// Cross product is Vector3D(a_y * b_z - a_z * b_y, a_z * b_x - a_x * b_z, a_x * b_y - a_y * b_x)
	return Vector3D(v3d1.y * v3d2.z - v3d1.z * v3d2.y, v3d1.z * v3d2.x - v3d1.x * v3d2.z, v3d1.x * v3d2.y - v3d1.y * v3d2.x);
}

double angle3d(const Vector3D& v3d1, const Vector3D& v3d2) {
	// Angle between vectors is cos^-1 ((a . b)/(|a|*|b|))
	return (int)std::acos((dot3d(v3d1, v3d2)) / (v3d1.magnitude() * v3d2.magnitude()));
}

