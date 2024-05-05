#include "miniRT.h"

bool	solveQuadratic(float a, float b, float c, float *t0, float *t1)
{
	float	discriminant;
	float	sqrt_discriminant;

	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.0f)
		return (false);
	else if (discriminant == 0.0f)
		*t0 = *t1 = -b / (2.0f * a);
	else
	{
		sqrt_discriminant = sqrt(discriminant);
		*t0 = (-b + sqrt_discriminant) / (2.0f * a);
		*t1 = (-b - sqrt_discriminant) / (2.0f * a);
	}
	return (true);
}

bool	hit_sphere(t_ray *ray, t_sp *sphere)
{
	t_vec	L;
    t_op op;

	L = subtract_vec(ray->origin, sphere->coordinates);
	op.a = dot_prod(ray->direction, ray->direction);
	op.b = 2.0f * dot_prod(ray->direction, L);
	op.c = dot_prod(L, L) - sphere->radius * sphere->radius;
	if (!solveQuadratic(op.a, op.b, op.c, &op.t0, &op.t1))
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
	return (true);
}
