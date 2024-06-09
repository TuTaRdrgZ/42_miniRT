/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:32:15 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:53:55 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_valid_filetype(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if (len <= 2)
		return (false);
	if (str[len - 2] != '.')
		return (false);
	if (str[len - 1] != 'r')
		return (false);
	if (str[len] != 't')
		return (false);
	return (true);
}

// check if all chars are correct
int	is_valid_char(char **matrix)
{
	int		i;
	int		j;
	char	*s;

	i = 1;
	j = 0;
	while (matrix[i])
	{
		s = matrix[i];
		j = 0;
		while (s[j])
		{
			if (s[j] != '-' && s[j] != '.' && s[j] != ',' && s[j] != ' '
				&& ft_isdigit(s[j]) == 0 && s[j] != '\n')
				return (printf(RED "Error\n" RST "Invalid char: "), i);
			j++;
		}
		i++;
	}
	return (OK);
}
