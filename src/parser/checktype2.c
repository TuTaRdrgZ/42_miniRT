/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktype2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 21:04:07 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/13 12:02:32 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_ssaa(t_data *data, char **matrix, int argc)
{
	char	line[2];
	int		rd;

	if (argc != 2)
		return (print_error("Invalid SSAA\n"), KO);
	data->ssaa = ft_atoi(matrix[1]);
	if (data->ssaa <= 1)
		data->ssaa = 0;
	if (data->ssaa > 8)
	{
		printf("That ssaa value is too high, do you want to continue? (y/N)\n");
		rd = read(0, line, 1);
		if (rd > 0)
		{
			line[rd] = '\0';
			if (!ft_strcmp(line, "y"))
				return (OK);
			else
				return (KO);
		}
	}
	return (OK);
}
