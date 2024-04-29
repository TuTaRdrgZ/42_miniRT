#include "vector.h"

/* Returns a vector with the absolute values of its components. */
t_vec	abs_vec(t_vec color)
{
	color.x = fabs(color.x);
	color.y = fabs(color.y);
	color.z = fabs(color.z);
	return (color);
}
