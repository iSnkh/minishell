/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:58:47 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/22 17:18:01 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_append_after(t_list *current, t_list *list)
{
	t_list	*next;

	if (!current || !list)
		return ;
	if (!current->next)
	{
		current->next = list;
		return ;
	}
	next = current->next;
	current->next = list;
	list->next = next;
}
