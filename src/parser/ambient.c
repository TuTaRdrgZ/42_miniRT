/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:31:50 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/07 01:33:12 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_ambient(char **ambient, int argc /*, t_data *data*/)
{
	int	returnval;

	if (argc != 3)
    {
		printf(RED "Error\n" RST "Bad arguments: (A)");
		return (print_matrix_error(ambient, -1), KO);
    }
	returnval = check_ratio(ambient[1]);
	if (returnval)
		return (print_matrix_error(ambient, returnval), KO);
	if (check_rgb(ambient[2]))
		return (KO);
	return (OK);
}
