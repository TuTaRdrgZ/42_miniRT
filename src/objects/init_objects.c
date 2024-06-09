/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:31:45 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:41:09 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "structures.h"

t_sp	*init_sphere(char **data)
{
	t_sp	*new;
	char	**split;

	new = ft_calloc(sizeof(t_sp), 1);
	if (!new)
		exit_error("Malloc failed");
	split = ft_split(data[1], ',');
	if (!split)
		exit_error("Malloc failed");
	new->coordinates = new_vec(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	new->diameter = ft_atof(data[2]);
	new->radius = new->diameter / 2.0;
	ft_free(split);
	split = ft_split(data[3], ',');
	if (!split)
		exit_error("Malloc failed");
	new->rgb.r = ft_atoi(split[0]);
	new->rgb.g = ft_atoi(split[1]);
	new->rgb.b = ft_atoi(split[2]);
	ft_free(split);
	return (new);
}

t_pl	*init_plane(char **data)
{
	t_pl	*new;
	char	**split;

	new = ft_calloc(sizeof(t_pl), 1);
	split = ft_split(data[1], ',');
	if (!new || !split)
		exit_error("Malloc failed");
	new->coordinates = new_vec(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	ft_free(split);
	split = ft_split(data[2], ',');
	if (!split)
		exit_error("Malloc failed");
	new->normal = new_vec(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	ft_free(split);
	split = ft_split(data[3], ',');
	if (!split)
		exit_error("Malloc failed");
	new->rgb.r = ft_atoi(split[0]);
	new->rgb.g = ft_atoi(split[1]);
	new->rgb.b = ft_atoi(split[2]);
	ft_free(split);
	return (new);
}

void	set_cy_color(t_cy *new, char **split)
{
	new->rgb.r = ft_atoi(split[0]);
	new->rgb.g = ft_atoi(split[1]);
	new->rgb.b = ft_atoi(split[2]);
}

t_cy	*init_cylinder(char **data)
{
	t_cy	*new;
	char	**split;

	new = ft_calloc(sizeof(t_cy), 1);
	split = ft_split(data[1], ',');
	if (!new || !split)
		exit_error("Malloc failed");
	new->coordinates = new_vec(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	ft_free(split);
	split = ft_split(data[2], ',');
	if (!split)
		exit_error("Malloc failed");
	new->normal = new_vec(ft_atof(split[0]), ft_atof(split[1]),
			ft_atof(split[2]));
	ft_free(split);
	new->diameter = ft_atof(data[3]);
	new->height = ft_atof(data[4]);
	split = ft_split(data[5], ',');
	if (!split)
		exit_error("Malloc failed");
	set_cy_color(new, split);
	ft_free(split);
	return (new);
}

void	init_obj(t_obj **obj, char **obj_data, int type)
{
	t_obj	*new;

	new = ft_calloc(sizeof(t_obj), 1);
	if (!new)
		exit_error("Malloc failed");
	new->next = NULL;
	new->type = type;
	if (type == SP)
		new->object = init_sphere(obj_data);
	else if (type == PL)
		new->object = init_plane(obj_data);
	else if (type == CY)
		new->object = init_cylinder(obj_data);
	if (!(*obj))
		*obj = new;
	else
		(find_last(obj))->next = new;
}
