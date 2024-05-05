#include "../lib/vector/vector.h"
#include <math.h>

int	main(void)
{
	t_vec	a;
	t_vec	b;
	t_vec	c;

	a = new_vec(1, 2, 3);
	print_vec(a);
	b = new_vec(4, 5, 6);
	print_vec(b);
	c = add_vec(a, b);
	print_vec(c);
	return (0);
}
