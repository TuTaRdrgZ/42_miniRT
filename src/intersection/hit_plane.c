/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 17:33:26 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 17:43:58 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	hit_plane(const t_ray *ray, const t_pl *plane, t_hit *hit)
{
	double	dn;
	double	t;
	double	d;

	dn = dot_prod(ray->direction, plane->normal);
	if (fabs(dn) < 0.00000001)
		return (false);
	d = dot_prod(plane->normal, plane->coordinates);
	t = (d - dot_prod(plane->normal, ray->origin)) / dn;
	if (t < 0.00000001 || t > 2147483647)
		return (false);
	hit->hit_point = add_vec(ray->origin, mult_by_scal(ray->direction, t));
	hit->normal = plane->normal;
	return (true);
}
