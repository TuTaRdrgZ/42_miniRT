#include "../../inc/miniRT.h"

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
	float	a;
	float	b;
	float	c;
	float	temp;

	float t0, t1;
	L = subtract_vec(ray->origin, sphere->coordinates);
	a = dot_prod(ray->direction, ray->direction);
	b = 2.0f * dot_prod(ray->direction, L);
	c = dot_prod(L, L) - sphere->radius * sphere->radius;
	if (!solveQuadratic(a, b, c, &t0, &t1))
		return (false);
	if (t0 > t1)
	{
		temp = t0;
		t0 = t1;
		t1 = temp;
	}
	if (t0 < 0)
	{
		t0 = t1; // If t0 is negative, let's use t1 instead
		if (t0 < 0)
			return (false); // Both t0 and t1 are negative
	}
	t1 = t0;
	return (true);
}
