/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtract_vectors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:58:55 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:58:56 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Subtracts two vectors.
Returns vector pointing from v2 to v1.*/
t_vec	subtract_vec(t_vec v1, t_vec v2)
{
	t_vec	result;

	result = v1;
	result.x -= v2.x;
	result.y -= v2.y;
	result.z -= v2.z;
	return (result);
}
