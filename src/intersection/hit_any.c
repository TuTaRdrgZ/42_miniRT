#include "miniRT.h"
#include "structures.h"
#include "vector.h"

float	distance_vec(t_vec p1, t_vec p2)
{
	t_vec	difference;

	difference = subtract_vec(p1, p2);
	return (sqrt(dot_prod(difference, difference)));
}

void	set_intersect(t_intersec *intersect, t_vec *normal, t_vec *hit_point)
{
	intersect->normal = *normal;
	intersect->hit_point = *hit_point;
	intersect->hit = 1;
}

float	create_intersection_point(t_obj **obj, t_ray *ray,
		t_intersec *intersect)
{
	t_vec	normal;
	t_vec	hit_point;

	if ((*obj)->type == SP)
	{
		if (hit_sphere(ray, (*obj)->object, &hit_point, &normal))
		{
			set_intersect(intersect, &normal, &hit_point);
			intersect->rgb = get_sphere_rgb((*obj)->object);
			return (distance_vec(ray->origin,
					subtract_vec(((t_sp *)(*obj)->object)->coordinates,
						ray->origin)));
		}
	}
	if ((*obj)->type == PL)
	{
		if (hit_plane(ray, (*obj)->object, &hit_point, &normal))
		{
			set_intersect(intersect, &normal, &hit_point);
			intersect->rgb = get_plane_rgb((*obj)->object);
			return (distance_vec(ray->origin,
					subtract_vec(((t_pl *)(*obj)->object)->coordinates,
						ray->origin)));
		}
	}
	intersect->hit = 0;
	return (0);
}

t_intersec	hit_any_object(t_obj **obj, t_ray *ray)
{
	t_obj		*tmp;
	t_intersec	closest_intersection;
	float		closest_distance;
	t_intersec	current_intersection;
	float		distance;

	tmp = *obj;
	closest_distance = INFINITY;
	closest_intersection.hit = 0;
	while (tmp)
	{
		current_intersection.hit = 0;
		distance = create_intersection_point(&tmp, ray, &current_intersection);
		if (current_intersection.hit)
		{
			if (distance < closest_distance)
			{
				closest_intersection = current_intersection;
				closest_distance = distance;
			}
		}
		tmp = tmp->next;
	}
	return (closest_intersection);
}

bool	hit_plane(const t_ray *ray, const t_pl *plane, t_vec *hit_point,
		t_vec *normal)
{
	float	dn;
	float	xv;
	float	t;

	dn = dot_prod(ray->direction, plane->normal);
	xv = dot_prod(subtract_vec(plane->coordinates, ray->origin), plane->normal);
	if (!dn || (dn > 0 && xv > 0) || (dn > 0 && xv > 0))
		return (false);
	t = -xv / dn;
	if (t <= 0.0001)
		return (false);
	return (true);
	*hit_point = add_vec(ray->origin, mult_vec_by_scal(ray->direction, t));
	*normal = plane->normal;
	return (true);
}
