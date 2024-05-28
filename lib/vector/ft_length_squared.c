#include "vector.h"

/* Returns the squared length of the vector. */
double length_sqrd(t_vec vector)
{
	return (vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}
