/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:42:21 by amonteli          #+#    #+#             */
/*   Updated: 2021/01/18 15:39:36 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

t_gnl	*ft_create_list(int fd)
{
	t_gnl	*lst;

	if (fd < 0 || (!(lst = malloc(sizeof(t_gnl)))))
		return (NULL);
	lst->fd = fd;
	lst->content = ft_strdup("");
	lst->next = NULL;
	return (lst);
}

t_gnl	*ft_lstchr(t_gnl *list, int fd)
{
	while (list)
	{
		if (list->fd == fd)
			return (list);
		list = list->next;
	}
	return (NULL);
}

t_gnl	*ft_lstadd(t_gnl **alst, t_gnl *new)
{
	if (alst)
		new->next = *alst;
	*alst = new;
	return (*alst);
}
