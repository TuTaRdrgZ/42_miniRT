#include "vector.h"

/*Multiplies every vector coordinate with f.*/
t_vec	mult_vec_by_scal(t_vec v1, double f)
{
	t_vec	result;

	result = v1;
	result.x *= f;
	result.y *= f;
	result.z *= f;
	return (result);
}
