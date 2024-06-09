/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuta <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 14:07:40 by tuta              #+#    #+#             */
/*   Updated: 2024/06/09 18:16:34 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *str, const char *sep, char **lasts)
{
	char	*w;

	if (!str)
		str = *lasts;
	while (*str && ft_strchr(sep, *str))
		++str;
	if (*str == '\0')
		return (NULL);
	w = str;
	while (*str && !ft_strchr(sep, *str))
		++str;
	if (*str)
		*str++ = '\0';
	*lasts = str;
	return (w);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*ptr;

	return (ft_strtok_r(str, delim, &ptr));
}
