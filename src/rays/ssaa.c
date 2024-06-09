/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:55:00 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 19:57:18 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec	calculate_sample_position(t_data *data, t_ssaa *ssaa)
{
	t_vec	sample_pos;
	float	u_offset;
	float	v_offset;

	u_offset = ((float)rand() / RAND_MAX) / data->ssaa;
	v_offset = ((float)rand() / RAND_MAX) / data->ssaa;
	sample_pos = add_vec(data->vp->pixel00,
			add_vec(mult_by_scal(data->vp->pixel_delta_u, ssaa->i + (ssaa->k
						+ u_offset) / data->ssaa),
				mult_by_scal(data->vp->pixel_delta_v, ssaa->j + (ssaa->l
						+ v_offset) / data->ssaa)));
	return (sample_pos);
}

static void	accumulate_color(t_data *data, t_rgb *total_color, t_ssaa *ssaa)
{
	t_vec	sample_pos;
	t_hit	hit;

	ssaa->k = 0;
	while (ssaa->k < data->ssaa)
	{
		ssaa->l = 0;
		while (ssaa->l < data->ssaa)
		{
			sample_pos = calculate_sample_position(data, ssaa);
			data->ray->direction = subtract_vec(sample_pos,
					data->camera->origin);
			hit = hit_any_object(&data->obj, data->ray);
			apply_lighting(&hit, *data->light, *data);
			total_color->r += hit.rgb.r;
			total_color->g += hit.rgb.g;
			total_color->b += hit.rgb.b;
			ssaa->l++;
		}
		ssaa->k++;
	}
}

static void	render_pixel(t_data *data, t_ssaa *ssaa, float num_samples)
{
	t_rgb	total_color;

	total_color.r = 0;
	total_color.g = 0;
	total_color.b = 0;
	accumulate_color(data, &total_color, ssaa);
	total_color.r /= num_samples;
	total_color.g /= num_samples;
	total_color.b /= num_samples;
	mlx_put_pixel(data->image, ssaa->i, ssaa->j,
		calculate_pixel_color(total_color));
}

void	render_scene_ssaa(void *param)
{
	t_data	*data;
	t_ssaa	ssaa;
	float	num_samples;

	data = (t_data *)param;
	data->ray->origin = data->camera->origin;
	num_samples = data->ssaa * data->ssaa;
	ssaa.j = 0;
	ssaa.k = 0;
	ssaa.l = 0;
	while (ssaa.j < data->height)
	{
		ssaa.i = 0;
		while (ssaa.i < data->width)
		{
			render_pixel(data, &ssaa, num_samples);
			ssaa.i++;
		}
		ssaa.j++;
	}
}
