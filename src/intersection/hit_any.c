#include "miniRT.h"
#include "structures.h"
#include "vector.h"

void	set_intersect(t_hit *hit, t_vec *normal, t_vec *hit_point)
{
	hit->normal = *normal;
	hit->hit_point = *hit_point;
	hit->didItHit = 1;
}

float	create_hit_point(t_obj **obj, t_ray *ray, t_hit *hit)
{
	t_vec	normal;
	t_vec	hit_point;

	if ((*obj)->type == SP)
	{
		if (hit_sphere(ray, (*obj)->object, &hit_point, &normal))
		{
			set_intersect(hit, &normal, &hit_point);
			hit->rgb = get_sphere_rgb((*obj)->object);
			return (distance_vec(ray->origin,
					subtract_vec(((t_sp *)(*obj)->object)->coordinates,
						ray->origin)));
		}
	}
	if ((*obj)->type == PL)
	{
		if (hit_plane(ray, (*obj)->object, &hit_point, &normal))
		{
			set_intersect(hit, &normal, &hit_point);
			hit->rgb = get_plane_rgb((*obj)->object);
			return (distance_vec(ray->origin,
					subtract_vec(((t_pl *)(*obj)->object)->coordinates,
						ray->origin)));
		}
	}
	if ((*obj)->type == CY)
	{
		if (hit_cylinder(ray, (*obj)->object, &hit_point, &normal))
		{
			set_intersect(hit, &normal, &hit_point);
			hit->rgb = get_cylinder_rgb((*obj)->object);
			return (distance_vec(ray->origin,
					subtract_vec(((t_cy *)(*obj)->object)->coordinates,
						ray->origin)));
		}
	}
	hit->didItHit = 0;
	return (0);
}

bool	simple_check_hit(t_obj **obj, t_vec hit_point, t_vec light)
{
	t_obj	*tmp;
	t_ray	ray;

	ray.origin = hit_point;
	ray.direction = subtract_vec(light, hit_point);

	tmp = *obj;
	while (tmp)
	{
		if (tmp->type == SP)
			if (hit_sphere(&ray, (t_sp *)tmp->object, 0, 0))
				return (true);
		if (tmp->type == PL)
			if (hit_plane(&ray, (t_pl *)tmp->object, 0, 0))
				return (true);
		// if (tmp->type == CY)
		// 	if (hit_cylinder(ray, (t_cy *)tmp->object, 0, 0))
		tmp = tmp->next;
	}
	return (false);
}

t_hit	hit_any_object(t_obj **obj, t_ray *ray)
{
	t_obj	*tmp;
	t_hit	closest_hit;
	float	closest_distance;
	t_hit	current_hit;
	float	distance;

	closest_distance = INFINITY;
	closest_hit.didItHit = 0;
	tmp = *obj;
	while (tmp)
	{
		current_hit.didItHit = 0;
		distance = create_hit_point(&tmp, ray, &current_hit);
		if (current_hit.didItHit)
		{
			if (distance < closest_distance)
			{
				closest_hit = current_hit;
				closest_distance = distance;
			}
		}
		tmp = tmp->next;
	}
	return (closest_hit);
}
