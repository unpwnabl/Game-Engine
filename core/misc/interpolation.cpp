#include "include/interpolation.hpp"

double lerp(double a, double b, double t) {
	if (t == 0.0) {
		// If we take 0 steps, we stay at a
		return a;
	} else if (t == 1.0) {
		// If we take 1 whole step, we get to b immediately
		return b;
	} else {
		return a + t * (b - a);
	}
}
