#include "miniRT.h"

bool	hit_plane(const t_ray *ray, const t_pl *plane, t_vec *hit_point,
		t_vec *normal)
{
	double dn;
	double t;
	double d;

	dn = dot_prod(ray->direction, plane->normal);
	if (fabs(dn) < 0.00000001)
		return (false);
	d = dot_prod(plane->normal, plane->coordinates);
	t = (d - dot_prod(plane->normal, ray->origin)) / dn;
	if (t < 0.00000001 || t > 2147483647)
		return (false);
    if (hit_point && normal)
    {
        *hit_point = add_vec(ray->origin, mult_vec_by_scal(ray->direction, t));
        *normal = plane->normal;
    }
	return (true);
}
