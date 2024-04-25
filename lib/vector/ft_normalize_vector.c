#include "vector.h"

/*Returns same vector with value of 1.*/
t_vec	normalize_vec(t_vec v1)
{
	double length = length_vec(v1);

	if (length != 0.0)
		return div_vec_by_scal(v1, length);
	return v1;

}
