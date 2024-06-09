/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:58:18 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:58:19 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Returns vector allocated on stack.*/
t_vec	new_vec(double x, double y, double z)
{
	t_vec	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}
