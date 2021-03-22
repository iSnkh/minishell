/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_append_lists.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:58:29 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/22 17:17:57 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_append_lsts(t_list *current, t_list *list)
{
	t_list	*start_next;
	t_list	*index;

	if (!current || !list)
		return ;
	if (!current->next)
	{
		current->next = list;
		return ;
	}
	start_next = current->next;
	current->next = list;
	index = list;
	while (index->next)
		index = index->next;
	index->next = start_next;
}
