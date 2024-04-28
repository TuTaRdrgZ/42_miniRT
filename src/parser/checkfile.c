/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkfile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuta <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 11:57:23 by tuta              #+#    #+#             */
/*   Updated: 2024/04/28 17:29:51 by tuta             ###   ########.fr       */
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
				return (printf(RED "Invalid char in string: %s (%c)\n" RST, s,
						s[j]));
			j++;
		}
		i++;
	}
	return (OK);
}

// function that checks the id and init all the objs
int	check_type(/*t_data *data, */ char **matrix)
{
	int	len;

	len = ft_strlen(matrix[0]);
	if (is_valid_char(matrix) == OK)
	{
		if (!ft_strncmp(matrix[0], "A", len))
        {
			printf("Hey found ambient light\n"); // init_ambient(matrix, data);
            if (check_ambient(matrix, arg_counter(matrix)) == KO)
                return (KO);
        }
		else if (!ft_strncmp(matrix[0], "L", len))
			printf("Hey found Light\n"); // init_light(matrix, data);
		else if (!ft_strncmp(matrix[0], "C", len))
			printf("Hey found camera here\n"); // init_camera()
		else if (!ft_strncmp(matrix[0], "sp", len))
			printf("Hey found a sphere\n"); // init_obj(data, "sphere");
		else if (!ft_strncmp(matrix[0], "cy", len))
			printf("Hey found a cylinder\n"); // init_obj(data, "sphere");
		else if (!ft_strncmp(matrix[0], "pl", len))
			printf("Hey found a plane\n"); // init_obj(data, "sphere");
		else
		{
			printf(RED "INVALID ID\n" RST);
			return (KO);
		}
		for (int i = 0; matrix[i]; i++)
			printf("line->%d |%s|\n", i, matrix[i]);
		printf("\n");
		return (OK);
	}
	return (KO);
}

int	main(void)
{
	char	*str;

	str = "test.rt";
	if (!is_valid_filetype(str))
		printf("nah, wrong filetype\n");
	read_file(str);
	return (0);
}
