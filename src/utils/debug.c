/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:02:34 by bautrodr          #+#    #+#             */
/*   Updated: 2024/06/09 19:13:22 by bautrodr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	print_sp(t_obj *node)
{
	t_sp	*sp;

	sp = (t_sp *)node->object;
	printf("Esfera:\n");
	printf("Nodo: %p\n", node);
	printf("Coordenadas: (%f, %f, %f)\n", sp->coordinates.x, sp->coordinates.y,
		sp->coordinates.z);
	printf("Color RGB: (%f, %f, %f)\n", sp->rgb.r, sp->rgb.g, sp->rgb.b);
	printf("Diámetro: %f\n", sp->diameter);
}

static void	print_pl(t_obj *node)
{
	t_pl	*pl;

	pl = (t_pl *)node->object;
	printf("Plano:\n");
	printf("Nodo: %p\n", node);
	printf("Coordenadas: (%f, %f, %f)\n", pl->coordinates.x, pl->coordinates.y,
		pl->coordinates.z);
	printf("Normal: (%f, %f, %f)\n", pl->normal.x, pl->normal.y, pl->normal.z);
	printf("Color RGB: (%f, %f, %f)\n", pl->rgb.r, pl->rgb.g, pl->rgb.b);
}

static void	print_cy(t_obj *node)
{
	t_cy	*cy;

	cy = (t_cy *)node->object;
	printf("Cilindro:\n");
	printf("Nodo: %p\n", node);
	printf("Coordenadas: (%f, %f, %f)\n", cy->coordinates.x, cy->coordinates.y,
		cy->coordinates.z);
	printf("Normal: (%f, %f, %f)\n", cy->normal.x, cy->normal.y, cy->normal.z);
	printf("Diámetro: %f\n", cy->diameter);
	printf("Altura: %f\n", cy->height);
	printf("Color RGB: (%f, %f, %f)\n", cy->rgb.r, cy->rgb.g, cy->rgb.b);
}

static void	print_obj_node(t_obj *node)
{
	if (node == NULL)
	{
		printf("Nodo NULL\n");
		return ;
	}
	printf("Tipo %d, ", node->type);
	if (node->type == SP)
		print_sp(node);
	else if (node->type == PL)
		print_pl(node);
	else if (node->type == CY)
		print_cy(node);
	else
		printf("Tipo de objeto desconocido: %d\n", node->type);
	printf("Siguiente nodo: %p\n\n", node->next);
}

void	print_all_nodes(t_data *data)
{
	t_obj	*obj;

	obj = data->obj;
	while (obj)
	{
		print_obj_node(obj);
		obj = obj->next;
	}
}
