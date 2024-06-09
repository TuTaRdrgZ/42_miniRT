/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:57:54 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:04:47 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	solve_cylinder_intersection(t_ray *ray, t_cy *cylinder, t_op *op)
{
	t_vec	oc;
	t_vec	axis;
	t_vec	dir_cross_axis;
	t_vec	oc_cross_axis;

	oc = subtract_vec(ray->origin, cylinder->coordinates);
	axis = normalize_vec(cylinder->normal);
	dir_cross_axis = cross_prod(ray->direction, axis);
	oc_cross_axis = cross_prod(oc, axis);
	op->a = dot_prod(dir_cross_axis, dir_cross_axis);
	op->b = 2 * dot_prod(dir_cross_axis, oc_cross_axis);
	op->c = dot_prod(oc_cross_axis, oc_cross_axis) - (cylinder->diameter / 2.0f)
		* (cylinder->diameter / 2.0f);
	if (!solve_quadratic(op))
		return (false);
	return (true);
}

static bool	validate_hit_point(t_ray *ray, t_cy *cylinder, t_op *op, t_hit *hit)
{
	t_vec	to_hit;
	t_vec	base_to_hit;
	t_vec	axis;
	float	projection;

	hit->t = op->t0;
	if (hit->t < 0)
	{
		hit->t = op->t1;
		if (hit->t < 0)
			return (false);
	}
	hit->hit_point = add_vec(ray->origin, mult_by_scal(ray->direction, hit->t));
	axis = normalize_vec(cylinder->normal);
	to_hit = subtract_vec(hit->hit_point, cylinder->coordinates);
	projection = dot_prod(to_hit, axis);
	if (projection < 0 || projection > cylinder->height)
		return (false);
	base_to_hit = subtract_vec(to_hit, mult_by_scal(axis, projection));
	hit->normal = normalize_vec(base_to_hit);
	return (true);
}

static bool	hit_cylinder_body(t_ray *ray, t_cy *cylinder, t_op *op, t_hit *hit)
{
	if (!solve_cylinder_intersection(ray, cylinder, op))
		return (false);
	if (!validate_hit_point(ray, cylinder, op, hit))
		return (false);
	return (true);
}

bool	hit_cylinder(t_ray *ray, t_cy *cylinder, t_hit *new_hit)
{
	t_op	op;
	t_hit	hit;
	bool	result;

	hit.hit_point = new_vec(0, 0, 0);
	hit.normal = new_vec(0, 0, 0);
	hit.t = INFINITY;
	result = caps(ray, &hit, new_hit, cylinder);
	if (hit_cylinder_body(ray, cylinder, &op, &hit))
	{
		new_hit->hit_point = hit.hit_point;
		new_hit->normal = hit.normal;
		result = true;
	}
	return (result);
}
