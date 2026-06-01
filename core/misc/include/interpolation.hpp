#ifndef INTERPOLATION_H
#define INTERPOLATION_H

// Linear interpolation for Rigidbody physics. Use the formula f(t) = a + t * (b - a) to calculate points using t as a normalized time value between 0.0 and 1
double lerp(double a, double b, double t);

#endif
