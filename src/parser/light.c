/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:32:34 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/07 01:33:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_light(char **light, int argc)
{
	if (argc != 4)
	{
		printf(RED "Error\n" RST "Bad arguments: (L)");
		return (print_matrix_error(light, -1), KO);
	}
	if (check_coordinates(light[1]))
		return (KO);
	if (check_ratio(light[2]))
		return (printf(RED "%s\n" RST, light[2]), KO);
	if (check_rgb(light[3]))
		return (KO);
	return (OK);
}
