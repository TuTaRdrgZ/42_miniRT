#include "vector.h"

/*Divides every vector coordinate by f. Checks for division by 0.*/
t_vec	div_vec_by_scal(t_vec v1, double f)
{
	t_vec	result;

	if (f == 0.0)
		return (v1);

	result.x = v1.x / f;
	result.y = v1.y / f;
	result.z = v1.z / f;
	return (result);
}
