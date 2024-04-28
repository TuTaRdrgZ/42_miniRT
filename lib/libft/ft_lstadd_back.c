/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bautrodr <bautrodr@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:48:52 by bautrodr          #+#    #+#             */
/*   Updated: 2024/04/28 12:34:48 by tuta             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/***************************************************************	
*						FT_LSTADD_BACK:						   *
*	La función ft_lstadd_back agrega un nuevo elemento `new_lst`   *
*	al final de una lista enlazada representada por un puntero *
*	a puntero `lst`. Si la lista está vacía, el puntero `lst`  *
*	se actualizará para apuntar al nuevo elemento. Si la lista *
*	no está vacía, el nuevo elemento se agregará al final de   *
*	la lista existente.										   *
*															   *	
*	Argumentos:												   *
*	lst: Un puntero a puntero que apunta al puntero inicial    *
*	     de la lista enlazada.								   *
*	new_lst: Un puntero al nuevo elemento que se agregará a la *
*	     lista.												   *
*															   *
*	Devuelve: Nada (void).									   *
*															   *
\**************************************************************/

void	ft_lstadd_back(t_list **lst, t_list *new_lst)
{
	if (!new_lst)
		return ;
	if (*lst == NULL)
		*lst = new_lst;
	else
		ft_lstlast(*lst)->next = new_lst;
}
