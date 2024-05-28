#include "vector.h"

/*prints the vector values as XYZ*/
void	print_vec(t_vec vector, char *name)
{
	printf("%s (%.4f|%.4f|%.4f)\n", name, vector.x, vector.y, vector.z);
}
