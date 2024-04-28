/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 12:12:30 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/28 12:35:23 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**************************************************************
*						FT_LSTADD_FRONT:					  *
*	La función ft_lstadd_front agrega un nuevo nodo `new_lst` al*
*	principio de una lista enlazada representada por un       *
*	puntero a puntero `lst`. Si la lista está vacía, el       *
*	puntero `lst` se actualizará para apuntar al nuevo nodo.  *
*	Si la lista no está vacía, el nuevo nodo se enlazará con  *
*	el nodo inicial existente y luego se actualizará el       *
*	puntero `lst` para apuntar al nuevo nodo.				  *
*															  *
*	Argumentos:												  *
*	lst: Un puntero a puntero que apunta al puntero inicial   *
*	     de la lista enlazada.								  *
*	new_lst: Un puntero al nuevo nodo que se agregará al inicio*
*	     de la lista.										  *
*															  *
*	Devuelve: Nada (void).									  *
*															  *
\*************************************************************/

void	ft_lstadd_front(t_list **lst, t_list *new_lst)
{
	if (!new_lst)
		return ;
	if (*lst == NULL)
		*lst = new_lst;
	else
	{
		new_lst->next = *lst;
		*lst = new_lst;
	}
}
