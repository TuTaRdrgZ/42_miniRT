/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checktype.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:32:26 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/07 15:41:25 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int check_resolution(t_data *data, char **matrix, int argc)
{
    if (argc != 3)
        return (print_error("Invalid Resolution\n"), KO);
    data->width = ft_atoi(matrix[1]);
    data->height = ft_atoi(matrix[2]);
    return (OK);
}

static int	check_type3(t_data *data, char **matrix)
{
	if (!ft_strcmp(matrix[0], "pl"))
	{
		if (check_obj(matrix, arg_counter(matrix), PL))
			return (KO);
		init_obj(&(data->obj), matrix, PL);
		return (OK);
	}
	else if (!ft_strcmp(matrix[0], "cy"))
	{
		if (check_obj(matrix, arg_counter(matrix), CY))
			return (KO);
		init_obj(&(data->obj), matrix, CY);
		return (OK);
	}
    else if (!ft_strcmp(matrix[0], "R"))
    {
        if (check_resolution(data, matrix, arg_counter(matrix)))
            return (KO);
        return (OK);
    }
	else
	{
		printf(RED "Error\nINVALID ID:" RST " \"%s\"\n", matrix[0]);
		return (KO);
	}
}

static int	check_type2(t_data *data, char **matrix)
{
	if (!ft_strcmp(matrix[0], "C"))
	{
		if (check_camera(matrix, arg_counter(matrix)))
			return (KO);
		camera_init(data->camera, matrix);
		return (OK);
	}
	else if (!ft_strcmp(matrix[0], "sp"))
	{
		if (check_obj(matrix, arg_counter(matrix), SP))
			return (KO);
		init_obj(&(data->obj), matrix, SP);
		return (OK);
	}
	return (check_type3(data, matrix));
}

// function that checks the id and init all the objs
int	check_type(t_data *data, char **matrix)
{
	int	retval;

    if (!matrix || !matrix[0])
        return (OK);
	retval = is_valid_char(matrix);
	if (retval)
		return (print_matrix_error(matrix, retval), KO);
	if (!ft_strcmp(matrix[0], "A"))
	{
		if (check_ambient(matrix, arg_counter(matrix)) == KO)
			return (KO);
		init_ambient(data->ambient, matrix);
		return (OK);
	}
	else if (!ft_strcmp(matrix[0], "L"))
	{
		if (check_light(matrix, arg_counter(matrix)) == KO)
			return (KO);
		init_light(data->light, matrix);
		return (OK);
	}
	return (check_type2(data, matrix));
}
