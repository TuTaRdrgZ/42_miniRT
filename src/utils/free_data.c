/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:03:29 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 19:04:27 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	free_all_objects(t_data *data)
{
	t_obj	*obj;
	t_obj	*tmp;

	obj = data->obj;
	while (obj)
	{
		tmp = obj->next;
		if (obj->object)
			free(obj->object);
		free(obj);
		obj = tmp;
	}
}

int	free_data(t_data *data)
{
	free(data->ray);
	free(data->camera);
	free(data->vp);
	free(data->ambient);
	free(data->light);
	free_all_objects(data);
	return (1);
}
