/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_caps.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:03:59 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:07:46 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_cylinder_caps(const t_ray *ray, t_cap *cap, t_hit *rec)
{
	t_vec	oc;
	t_vec	p;
	t_vec	to_center;
	double	denom;
	double	t;

	denom = dot_prod(cap->direction, ray->direction);
	if (fabs(denom) < 1e-6f)
		return (false);
	oc = subtract_vec(cap->coordinates, ray->origin);
	t = dot_prod(oc, cap->direction) / denom;
	if (t <= 1e-6f || t >= rec->t)
		return (false);
	p = ray_at(ray, t);
	to_center = subtract_vec(p, cap->coordinates);
	if (dot_prod(to_center, to_center) > cap->radius * cap->radius)
		return (false);
	rec->t = t;
	rec->hit_point = p;
	rec->normal = mult_by_scal(cap->direction, -1);
	return (true);
}

bool	caps(t_ray *ray, t_hit *hit, t_hit *new_hit, t_cy *cylinder)
{
	bool	result;
	t_cap	cap;

	result = false;
	cap.coordinates = cylinder->coordinates;
	cap.direction = cylinder->normal;
	cap.radius = cylinder->diameter / 2;
	if (hit_cylinder_caps(ray, &cap, hit))
	{
		new_hit->hit_point = hit->hit_point;
		new_hit->normal = hit->normal;
		result = true;
	}
	cap.coordinates = add_vec(cylinder->coordinates,
			mult_by_scal(normalize_vec(cylinder->normal), cylinder->height));
	cap.direction = mult_by_scal(cylinder->normal, -1);
	if (hit_cylinder_caps(ray, &cap, hit))
	{
		new_hit->hit_point = hit->hit_point;
		new_hit->normal = hit->normal;
		result = true;
	}
	return (result);
}
