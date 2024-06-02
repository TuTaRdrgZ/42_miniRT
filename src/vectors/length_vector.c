#include "miniRT.h"

/*Returns length of vector.*/
double	length_vec(t_vec v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}
