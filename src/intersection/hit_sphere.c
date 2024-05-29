#include "miniRT.h"

bool	solve_quadratic(t_op *op)
{
	float	discriminant;
	float	sqrt_discriminant;

	discriminant = op->b * op->b - 4.0f * op->a * op->c;
	if (discriminant < 0.0f)
		return (false);
	else if (discriminant == 0.0f)
		op->t0 = op->t1 = -(op->b) / (2.0f * op->a);
	else
	{
		sqrt_discriminant = sqrt(discriminant);
		op->t0 = (-(op->b) + sqrt_discriminant) / (2.0f * op->a);
		op->t1 = (-(op->b) - sqrt_discriminant) / (2.0f * op->a);
	}
	return (true);
}

bool	hit_sphere(t_ray *ray, t_sp *sphere, t_vec *hit_point, t_vec *normal)
{
	t_vec	L;
	t_op	op;

	L = subtract_vec(ray->origin, sphere->coordinates);
	op.a = dot_prod(ray->direction, ray->direction);
	op.b = 2.0f * dot_prod(ray->direction, L);
	op.c = dot_prod(L, L) - sphere->radius * sphere->radius;
	if (!solve_quadratic(&op))
		return (false);
	if (op.t0 > op.t1)
	{
		op.temp = op.t0;
		op.t0 = op.t1;
		op.t1 = op.temp;
	}
	if (op.t0 < 0)
	{
		op.t0 = op.t1; // If t0 is negative, let's use t1 instead
		if (op.t0 < 0)
			return (false); // Both t0 and t1 are negative
	}
    if (hit_point && normal)
    {
        *hit_point = add_vec(ray->origin, mult_vec_by_scal(ray->direction, op.t0));
        *normal = subtract_vec(*hit_point, sphere->coordinates);
        *normal = normalize_vec(*normal);
    }
	return (true);
}
