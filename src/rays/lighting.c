/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:07:58 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/13 11:33:49 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	ray_at(const t_ray *ray, double t)
{
	t_vec	dir;

	dir = ray->direction;
	dir = mult_by_scal(dir, t);
	return (add_vec(ray->origin, dir));
}

t_rgb	fade_to_shade(t_rgb color, double fade_factor)
{
	if (fade_factor > 1)
		fade_factor = 1;
	color.r *= fade_factor;
	color.g *= fade_factor;
	color.b *= fade_factor;
	return (color);
}

void	apply_lighting(t_hit *hit, t_light light, t_data data)
{
	t_vec	light_direction;
	float	cos_angle;
	float	dot_product;

	light_direction = new_vec(0, 0, 0);
	light_direction = normalize_vec(subtract_vec(light.coordinates,
				hit->hit_point));
	dot_product = dot_prod(hit->normal, light_direction);
	cos_angle = dot_product / (length_vec(hit->normal)
			* length_vec(light_direction));
	if (cos_angle > 0 && !simple_check_hit(data.obj, hit,
			data.light->coordinates))
		hit->rgb = fade_to_shade(hit->rgb, (data.ambient->ratio + (light.ratio
						* cos_angle)));
	else
		hit->rgb = fade_to_shade(hit->rgb, data.ambient->ratio);
	hit->rgb.r = (hit->rgb.r / 255) * data.ambient->rgb.r * data.ambient->ratio
		+ hit->rgb.r * (1 - data.ambient->ratio);
	hit->rgb.g = (hit->rgb.g / 255) * data.ambient->rgb.g * data.ambient->ratio
		+ hit->rgb.g * (1 - data.ambient->ratio);
	hit->rgb.b = (hit->rgb.b / 255) * data.ambient->rgb.b * data.ambient->ratio
		+ hit->rgb.b * (1 - data.ambient->ratio);
}
