/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr bautrodr@student.42barcelona      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:57:28 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/29 00:58:41 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *n)
{
	int		i;
	int		j;
	float	nb;
	int		m;

	i = 0;
	nb = 0;
	m = 1;
	j = 1;
	if (n[i] == '-')
	{
		m = -m;
		i++;
	}
	while (n[i])
	{
		if (j > 1 && n[i - 1] != '.')
			j *= 10;
		if (n[i] == '.')
			j *= 10;
		else
			nb = nb * 10 + (n[i] - 48);
		i++;
	}
	return (m * nb / j);
}
