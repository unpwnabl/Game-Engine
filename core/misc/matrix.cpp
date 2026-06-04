#include <iostream>

#include "include/matrix.hpp"
#include "../../src/2d/include/vector2d.hpp"

// Thanks to Daniel Shiffman for the inspirations for the functions and explanations.
// See more here: https://www.youtube.com/watch?v=tzsgS19RRc8

void print_matrix2d(float* m, int r, int c) {
	std::cout << r << " x " <<  c << std::endl;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			std::cout << *((m + i * c) + j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

float* matrix2d_sum(float* m1, float* m2, int r, int c) {
	// Initialize new float 2D array with 0 with dimensions r x c
	float* result = new float[r * c]{0};

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			*((result + i * c) + j) = (*((m1 + i * c) + j)) + (*((m2 + i * c) + j));
		}
	}

	return result;
}

float* matrix2d_scale(float* m, int r, int c, float scalar) {
	// Initialize new float 2D array with 0 with dimensions r x c
	float* result = new float[r * c]{0};

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			*((result + i * c) + j) = (*((m + i * c) + j)) * scalar;
		}
	}

	return result;
}

float* matrix2d_mult(float* m1, int r1, int c1, float* m2, int r2, int c2) {
	if (c1 != r2) {
		std::cout << "[X] Matrices have incompatible numers of rows and columns" << std::endl;
		return nullptr;
	}
	
	// Initialize new float 2D array with 0 with dimensions r1 x c2
	float* result = new float[r1 * c2]{0};

	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c2; j++) {
			float sum = 0;
			for (int k = 0; k < c1; k++) {
				// Fuck pointers
				// sum += m1[i][k] * m2[k][j]
				sum += (*((m1 + i * c1) + k)) * (*((m2 + k * c2) +j));
			}
			// result[i][j] = sum;
			*((result + i * c2) + j) = sum;
		}
	}
	return result;
}

float* vect2d_to_matrix(Vector2D v) {
	// Initialize new float 2D array with 0 with dimensions 2 x 1
	float* result = new float[2 * 1]{0};
	*((result + 0 * 1) + 0) = v.x;
	*((result + 1 * 1) + 0) = v.y;

	return result;
}

Vector2D matrix_to_vect2d(float* m, int r, int c) {
	Vector2D result;
	result.x = *((m + 0 * c) + 0);
	result.y = *((m + 1 * c) + 0);

	return result;
}
