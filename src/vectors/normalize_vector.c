/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:59:02 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:59:31 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Returns same vector with value of 1.*/
t_vec	normalize_vec(t_vec v1)
{
	double	length;

	length = length_vec(v1);
	if (length != 0.0)
		return (div_by_scal(v1, length));
	return (v1);
}
