/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RGB.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:32:40 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/07 01:33:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	check_rgb2(char **rgb, char *str)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (rgb[++i])
	{
		j = -1;
		while (rgb[i][++j])
			if (!ft_isdigit(rgb[i][j]))
				return (printf(RED "Error\nInvalid RGB: %s\n" RST, str),
					ft_free(rgb), KO);
	}
	return (OK);
}

int	check_rgb(char *str)
{
	char	**rgb;
	int		rgb_colors[3];

	rgb = ft_split(str, ',');
	if (!rgb)
		return (printf("Malloc failed\n"), KO);
	if (arg_counter(rgb) != 3)
		return (print_error("Error: RGB="), print_matrix_error(rgb, -1), ft_free(rgb), KO);
	if (check_rgb2(rgb, str))
		return (KO);
	rgb_colors[0] = ft_atoi(rgb[0]);
	rgb_colors[1] = ft_atoi(rgb[1]);
	rgb_colors[2] = ft_atoi(rgb[2]);
	if (rgb_colors[0] > 255 || rgb_colors[0] < 0 || rgb_colors[1] > 255
		|| rgb_colors[1] < 0 || rgb_colors[2] > 255 || rgb_colors[2] < 0)
		return (printf(RED "Error\nInvalid RGB: %s\n" RST, str), ft_free(rgb),
			KO);
	return (ft_free(rgb), OK);
}
