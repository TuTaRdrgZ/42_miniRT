/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 01:31:58 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 18:54:31 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parser.h"

int	check_duplicated(t_data *data)
{
	if (data->ambient->total != 1)
		return (printf(RED "Error!\nOnly one ambient light allowed\n" RST), KO);
	if (data->camera->total != 1)
		return (printf(RED "Error!\nOnly one camera allowed\n" RST), KO);
	if (data->light->total != 1)
		return (printf(RED "Error!\nOnly one light allowed\n" RST), KO);
	if (!data->width || !data->height)
		return (printf(RED "Error!\nNot resolution found\n" RST), KO);
	return (OK);
}
