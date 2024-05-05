/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:48:53 by bautrodr          #+#    #+#             */
/*   Updated: 2024/05/05 19:49:24 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
 
int     ft_strcmp(char *s1, char *s2)
{
        int     i;

        i = 0;
        if (!s1 || !s2)
                return (0);
        while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
                i++;
        return (s1[i] - s2[i]);
}
