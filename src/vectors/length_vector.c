/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:58:37 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:58:38 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*Returns length of vector.*/
double	length_vec(t_vec v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}
