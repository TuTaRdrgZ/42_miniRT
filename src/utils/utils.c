/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:27:37 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:37:07 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_obj	*find_last(t_obj **obj)
{
	t_obj	*temp;

	if (!*obj)
		return (*obj);
	temp = *obj;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

void	exit_error(char *msg)
{
	printf(RED"%s\n"RST, msg);
	exit (-1);
}
