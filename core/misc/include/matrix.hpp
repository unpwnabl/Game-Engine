#ifndef MATRIX_H
#define MATRIX_H

#include "../../../src/2d/include/vector2d.hpp"
#include "../../../src/3d/include/vector3d.hpp"

void print_matrix(float* m, int r, int c);

float* matrix_sum(float* m1, float* m2, int r, int c);

float* matrix_scale(float* m, int r, int c, float scalar);

float* matrix_mult(float* m1, int r1, int c1, float* m2, int r2, int c2);

float* vect2d_to_matrix(Vector2D v);

Vector2D matrix_to_vect2d(float* m, int r, int c);

float* vect3d_to_matrix(Vector3D v);

Vector3D matrix_to_vect3d(float* m, int r, int c);

#endif
