
#ifndef LIBVEC_H
# define LIBVEC_H

# include <stdio.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vec;

typedef t_vec	t_color;
typedef t_vec	t_point;

t_vec	add_vec(t_vec v1, t_vec v2);
t_vec	subtract_vec(t_vec v1, t_vec v2);
t_vec	mult_vec(t_vec v1, t_vec v2);

t_vec	mult_vec_by_scal(t_vec v1, double scalar);
t_vec	div_vec_by_scal(t_vec v1, double scalar);

double	dot_prod(t_vec v1, t_vec v2);
t_vec	cross_prod(t_vec v1, t_vec v2);

t_vec	normalize_vec(t_vec v1);

t_vec	new_vec(double x, double y, double z);
t_vec	invert_vec(t_vec vec);
t_vec	abs_vec(t_vec color);

double	length_vec(t_vec v1);
double	length_sqrd(t_vec vector);
void	print_vec(t_vec vector, char *name);

bool	are_equal_vectors(t_vec a, t_vec b);

#endif
