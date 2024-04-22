#include "vector.h"

//compare vector a and b and return true if they are identically
bool	are_equal_vectors(t_vec a, t_vec b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z);
}
