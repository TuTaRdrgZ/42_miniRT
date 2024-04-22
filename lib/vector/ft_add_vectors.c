#include "vector.h"

/*Adds two vectors.*/
t_vec	add_vectors(t_vec v1, t_vec v2)
{
	t_vec	result;

	result = v1;
	result.x += v2.x;
	result.y += v2.y;
	result.z += v2.z;
	return (result);
}
