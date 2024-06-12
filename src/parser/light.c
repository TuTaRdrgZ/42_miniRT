/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:32:34 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/12 18:57:47 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_light(char **light, int argc)
{
	if (argc != 3)
	{
		printf(RED "Error\n" RST "Bad arguments: (L)");
		return (print_matrix_error(light, -1), KO);
	}
	if (check_coordinates(light[1]))
		return (KO);
	if (check_ratio(light[2]))
		return (printf(RED "%s\n" RST, light[2]), KO);
	return (OK);
}
