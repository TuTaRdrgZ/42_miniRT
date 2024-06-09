/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:32:48 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:36:17 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

t_rgb	get_cylinder_rgb(t_cy *cylinder)
{
	t_rgb	color;

	color.r = cylinder->rgb.r;
	color.g = cylinder->rgb.g;
	color.b = cylinder->rgb.b;
	return (color);
}
