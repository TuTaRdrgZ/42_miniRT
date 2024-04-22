#include "vector.h"

/*Multiplies every vector coordinate with f.*/
t_vec	multiply_vector_by_scalar(t_vec v1, double f)
{
	t_vec	result;

	result = v1;
	result.x *= f;
	result.y *= f;
	result.z *= f;
	return (result);
}
