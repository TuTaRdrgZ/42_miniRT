#include "miniRT.h"
#include "structures.h"
#include "vector.h"

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

void    set_intersect(t_hit *hit, t_vec *normal, t_vec *hit_point)
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
	hit->didItHit = 0;
	return (0);
}

t_hit hit_any_object(t_obj **obj, t_ray *ray)
{
    t_obj *tmp = *obj;
    t_hit closest_hit;
    float closest_distance = INFINITY;
    t_hit current_hit;
    float       distance;

    closest_hit.didItHit = 0;
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
