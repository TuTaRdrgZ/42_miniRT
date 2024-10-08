/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply_vector_by_scalar.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:59:14 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:59:15 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Multiplies every vector coordinate with f.*/
t_vec	mult_by_scal(t_vec v1, double f)
{
	t_vec	result;

	result = v1;
	result.x *= f;
	result.y *= f;
	result.z *= f;
	return (result);
}
