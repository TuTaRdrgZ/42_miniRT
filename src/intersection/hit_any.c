#include "miniRT.h"
#include <lib/vector/vector.h>

float	distance_vec(t_vec p1, t_vec p2)
{
	t_vec	difference;

	difference = subtract_vec(p1, p2);
	return (sqrt(dot_prod(difference, difference)));
}

t_rgb	get_sphere_rgb(t_sp *sphere)
{
	t_rgb	color;

	color.r = sphere->rgb.r;
	color.g = sphere->rgb.g;
	color.b = sphere->rgb.b;
	return (color);
}

t_rgb	get_plane_rgb(t_pl *plane)
{
	t_rgb	color;

	color.r = plane->rgb.r;
	color.g = plane->rgb.g;
	color.b = plane->rgb.b;
	return (color);
}

int	create_intersection_point(t_obj **obj, t_ray *ray, t_intersec *intersect)
{
	t_vec			normal;
	t_vec			hit_point;

	if ((*obj)->type == SP)
	{
		if (hit_sphere(ray, (*obj)->object, &hit_point, &normal))
		{
			intersect->normal = normal;
			intersect->hit_point = hit_point;
			intersect->rgb = get_sphere_rgb((*obj)->object);
			return (1);
		}
	}
	if ((*obj)->type == PL)
	{
		if (hit_plane(ray, (*obj)->object, &hit_point, &normal))
		{
			intersect->normal = normal;
			intersect->hit_point = hit_point;
			intersect->rgb = get_plane_rgb((*obj)->object);
			return (1);
		}
	}
	return (0);
}

t_intersec	hit_any_object(t_obj **obj, t_ray *ray, t_data *data)
{
	t_obj	*tmp;
	t_intersec	intersect;

	(void)data;
	tmp = *obj;
	while (tmp)
	{
		if (create_intersection_point(obj, ray, &intersect))
			return (intersect);
		tmp = tmp->next;
	}
	return (intersect);
}

bool	hit_plane(const t_ray *ray, const t_pl *plane, t_vec *hit_point, t_vec *normal)
{
    float dn;
    float xv;
    float t;

    dn = dot_prod(ray->direction, plane->normal);
    xv = dot_prod(subtract_vec(plane->coordinates, ray->origin), plane->normal);
    if (fabs(dn) < 1e-6)
        return false;
    t = xv / dn;
    if (t <= 0.0001)
        return false;
    *hit_point = add_vec(ray->origin, mult_vec_by_scal(ray->direction, t));
    *normal = plane->normal;
    return true;
}
