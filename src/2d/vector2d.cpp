#include <iostream>
#include <cmath>

#include "include/vector2d.hpp"
#include "../3d/include/vector3d.hpp"

Vector2D::Vector2D() : x(0.0), y(0.0) {};

Vector2D::Vector2D(double x_pos, double y_pos) : x(x_pos), y(y_pos) {};

Vector2D Vector2D::operator+(const Vector2D& v2d) const {
	return Vector2D(x + v2d.x, y + v2d.y);
}

Vector2D Vector2D::operator-(const Vector2D& v2d) const {
	return Vector2D(x + (-1.0 * v2d.x), y + (-1.0 * v2d.y));
}

Vector2D Vector2D::operator*(const double s) const {
	return Vector2D(x * s, y * s);
}

bool Vector2D::operator==(const Vector2D& v2d) const {
	if (x == v2d.x && y == v2d.y) {
		return true;
	}
	return false;
}

bool Vector2D::operator!=(const Vector2D& v2d) const {
	if (x != v2d.x || y != v2d.y) {
		return true;
	}
	return false;
}

bool Vector2D::operator<(const Vector2D& v2d) const {
	if (x < v2d.x && y < v2d.y) {
		return true;
	}
	return false;
}

bool Vector2D::operator>(const Vector2D& v2d) const {
	if (x > v2d.x && y > v2d.y) {
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Vector2D& v2d) {
	return os << "Vector2D(" << v2d.x << ", " << v2d.y << ")";
}

double Vector2D::magnitude() const {
	return std::sqrt((x * x) + (y * y));
}

Vector2D to_vect2d(const Vector3D& v3d) {
	return Vector2D(v3d.x, v3d.y);
}

double dot2d(const Vector2D& v2d1, const Vector2D& v2d2) {
	// Dot product is x1 * x2 + y1 * y2
	return v2d1.x * v2d2.x + v2d1.y * v2d2.y;
}

double angle2d(const Vector2D& v2d1, const Vector2D& v2d2) {
	// Angle between vectors is cos^-1 ((a . b)/(|a|*|b|))
	return std::acos(dot2d(v2d1, v2d2) / (v2d1.magnitude() * v2d2.magnitude()));
}
