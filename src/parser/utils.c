/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:32:44 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:44:20 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	arg_counter(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	print_error(char *error)
{
	printf(RED "%s" RST, error);
	return (KO);
}

char	*ft_strtrimfree(char *str, char *s)
{
	char	*new;

	new = ft_strtrim(str, s);
	if (str)
		free(str);
	return (new);
}

void	trim_matrix(char **matrix, char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (matrix[i])
	{
		tmp = ft_strtrim(matrix[i], s);
		free(matrix[i]);
		matrix[i] = tmp;
		i++;
	}
}

void	ft_free(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
