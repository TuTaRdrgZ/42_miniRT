#include "vector.h"

/* Scalar product of two vectors returns the angle between two vectors.
A value of 0 means they are orthogonal. */
double dot_prod(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
