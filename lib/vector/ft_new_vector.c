#include "vector.h"

/*Returns vector allocated on stack.*/
t_vec	new_vec(double x, double y, double z)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}
