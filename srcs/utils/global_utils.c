/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:15:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/25 13:50:20 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_console(void)
{
	ft_printf("\033[H\033[J");
}

t_token	*create_token(char *token, int flags)
{
	t_token	*lst;

	lst = malloc(sizeof(t_token));
	if (!lst)
		return (NULL);
	lst->token = token;
	if (flags)
		lst->flags = flags;
	else
		lst->flags = 0;
	return (lst);
}

int		is_escaped(t_token *token)
{
	if (token->flags & MS_SLASH || token->flags & MS_QUOTES || token->flags & MS_DQUOTES)
		return (1);
	return (0);
}

int		is_cmd_sep(char c)
{
	if (ft_strchr(CMD_SEPS, c))
		return (1);
	return (0);
}
