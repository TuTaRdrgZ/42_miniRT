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

bool	hit_any_object(t_obj **obj, t_ray *ray, int i, int j, t_data *data)
{
	t_obj	*tmp;
	bool	found_intersection;
	t_rgb	closest_color;
	float	t;

	found_intersection = false;
	float closest_t = INFINITY; // Initialize to a very large value
	tmp = *obj;
	while (tmp)
	{
		if (tmp->type == SP)
		{
			if (hit_sphere(ray, tmp->object))
			{
				t = distance_vec(ray->origin,
                        subtract_vec(((t_sp *)tmp->object)->coordinates,
							ray->origin));
				if (t < closest_t)	// Check if this is the closest intersection so far
				{
					closest_t = t;
					closest_color = get_sphere_rgb((t_sp *)tmp->object);
					found_intersection = true;
				}
			}
		}
		if (tmp->type == PL)
		{
			if (hit_plane(ray, (t_pl *)tmp->object))
			{
				t = distance_vec(ray->origin,
						subtract_vec(((t_pl *)tmp->object)->coordinates,
							ray->origin));
				if (t < closest_t)
					// Check if this is the closest intersection so far
				{
					closest_t = t;
					closest_color = get_plane_rgb((t_pl *)tmp->object);
					found_intersection = true;
				}
			}
		}
		tmp = tmp->next;
	}
	if (found_intersection)
		mlx_put_pixel(data->image, i, j, ft_pixel(closest_color));
	return (found_intersection);
}

bool	hit_plane(const t_ray *ray, const t_pl *plane)
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
}
