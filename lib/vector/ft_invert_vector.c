#include "vector.h"

/*Multiplies every coordinate with -1.*/
t_vec	invert_vector(t_vec vec)
{
	t_vec	result;

	result.x = -vec.x;
	result.y = -vec.y;
	result.z = -vec.z;
	return (result);
}
