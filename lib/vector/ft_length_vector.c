#include "vector.h"

/*Returns length of vector.*/
double	length_vector(t_vec v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}
