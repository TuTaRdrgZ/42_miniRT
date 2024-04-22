#include "vector.h"

/*Returns same vector with value of 1.*/
t_vec	normalize_vector(t_vec v1)
{
	double length = length_vector(v1);

	if (length != 0.0)
		return divide_vector_by_scalar(v1, length);
	return v1;

}
