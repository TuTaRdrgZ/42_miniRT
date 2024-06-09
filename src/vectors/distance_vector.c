/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_vector.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:58:49 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:58:50 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Returns distance between two vectors.*/
float	distance_vec(t_vec p1, t_vec p2)
{
	t_vec	difference;

	difference = subtract_vec(p1, p2);
	return (sqrt(dot_prod(difference, difference)));
}
