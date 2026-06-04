#ifndef MATRIX_H
#define MATRIX_H

#include "../../../src/2d/include/vector2d.hpp"

void print_matrix2d(float* m, int r, int c);

float* matrix2d_sum(float* m1, float* m2, int r, int c);

float* matrix2d_scale(float* m, int r, int c, float scalar);

float* matrix2d_mult(float* m1, int r1, int c1, float* m2, int r2, int c2);

float* vect2d_to_matrix(Vector2D v);

Vector2D matrix_to_vect2d(float* m, int r, int c);

#endif
