/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkobj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:32:21 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/13 13:47:05 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_sphere(char **sphere);
int	check_plane(char **plane);
int	check_cylinder(char **cylinder);

int	check_obj(char **matrix, int argc, int type)
{
	if ((argc != 4 && (type == SP || type == PL)) || (type == CY && argc != 6))
	{
		printf(RED "Error\n" RST "Bad arguments: ");
		return (print_matrix_error(matrix, -1), KO);
	}
	if (type == SP)
		if (check_sphere(matrix))
			return (KO);
	if (type == PL)
		if (check_plane(matrix))
			return (KO);
	if (type == CY)
		if (check_cylinder(matrix))
			return (KO);
	return (OK);
}

int	check_sphere(char **sphere)
{
	if (check_coordinates(sphere[1]))
		return (KO);
	if (check_diameter(sphere[2]))
		return (KO);
	if (check_rgb(sphere[3]))
		return (KO);
	return (OK);
}

int	check_plane(char **plane)
{
	if (check_coordinates(plane[1]))
		return (KO);
	if (check_normalized_vector(plane[2]))
		return (KO);
	if (check_rgb(plane[3]))
		return (KO);
	return (OK);
}

int	check_cylinder(char **cylinder)
{
	if (check_coordinates(cylinder[1]))
		return (KO);
	if (check_normalized_vector(cylinder[2]))
		return (KO);
	if (check_diameter(cylinder[3]))
		return (KO);
	if (check_diameter(cylinder[4]))
		return (KO);
	if (check_rgb(cylinder[5]))
		return (KO);
	return (OK);
}
