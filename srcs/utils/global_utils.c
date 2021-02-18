/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:15:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/18 17:58:35 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_console(void)
{
	ft_printf("\033[H\033[J");
}

t_cmd	*create_cmd(char *command)
{
	t_cmd	*lst;

	if (!(lst = malloc(sizeof(t_cmd))))
		return (NULL);
	lst->cmd = command;
	lst->parser = NULL;
	return (lst);
}

t_token	*create_token(char *token, int flags)
{
	t_token	*lst;

	if (!(lst = malloc(sizeof(t_token))))
		return (NULL);
	lst->token = token;
	if (flags)
		lst->flags = flags;
	else
		lst->flags = 0;
	return (lst);
}
