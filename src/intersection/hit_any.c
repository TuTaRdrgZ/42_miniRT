/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_any.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:42:26 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:12:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "structures.h"

static void	set_intersect(t_hit *hit, t_hit *new_hit)
{
	hit->normal = new_hit->normal;
	hit->hit_point = new_hit->hit_point;
	hit->did_it_hit = 1;
}

float	create_hit_point_aux(t_obj **obj, t_ray *ray, t_hit *hit)
{
	t_hit	new_hit;

	if ((*obj)->type == CY)
	{
		if (hit_cylinder(ray, (*obj)->object, &new_hit))
		{
			set_intersect(hit, &new_hit);
			hit->rgb = get_cylinder_rgb((*obj)->object);
			return (distance_vec(ray->origin, hit->hit_point));
		}
	}
	return (-1);
}

float	create_hit_point(t_obj **obj, t_ray *ray, t_hit *hit)
{
	t_hit	new_hit;

	if ((*obj)->type == SP)
	{
		if (hit_sphere(ray, (*obj)->object, &new_hit))
		{
			set_intersect(hit, &new_hit);
			hit->rgb = get_sphere_rgb((*obj)->object);
			return (distance_vec(ray->origin, hit->hit_point));
		}
	}
	if ((*obj)->type == PL)
	{
		if (hit_plane(ray, (*obj)->object, &new_hit))
		{
			set_intersect(hit, &new_hit);
			hit->rgb = get_plane_rgb((*obj)->object);
			return (distance_vec(ray->origin, hit->hit_point));
		}
	}
	return (create_hit_point_aux(obj, ray, hit));
}

bool	simple_check_hit(t_obj *obj, t_hit *hit, t_vec light)
{
	t_ray	ray;
	t_obj	*tmp;
	double	max_distance;
	t_hit	current_hit;
	float	distance;

	ray.origin = add_vec(hit->hit_point, mult_by_scal(hit->normal, 0.01));
	ray.direction = subtract_vec(light, ray.origin);
	max_distance = distance_vec(ray.origin, light);
	tmp = obj;
	while (tmp)
	{
		current_hit.did_it_hit = 0;
		distance = create_hit_point(&tmp, &ray, &current_hit);
		if (current_hit.did_it_hit == 1 && (distance <= max_distance))
			return (true);
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
	closest_hit.did_it_hit = 0;
	closest_hit.rgb = new_rgb(0, 0, 0);
	tmp = *obj;
	while (tmp)
	{
		current_hit.did_it_hit = 0;
		distance = create_hit_point(&tmp, ray, &current_hit);
		if (current_hit.did_it_hit == 1 && distance != -1)
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
