/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/06 16:32:37 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	flags_tokens()
{
	t_list *lst;

	lst = ms->tokens;
	while (lst)
	{
		t_token *tokenList;

		tokenList = (t_token *)lst->content;
		ft_printf("{%s}\n", tokenList->token);
		if (!(tokenList->flags & MS_SLASH || tokenList->flags & MS_QUOTES || tokenList->flags & MS_DQUOTES))
		{
			if (!ft_strchr(tokenList->token, '\\'))
			{
				// TODO: la il trouve pas de backslash donc flags tout proprement
			}
			ft_printf("hello\n");
		}
		lst = lst->next;
	}
}

void	*print_tokens(void *content)
{
	t_token	*token = (t_token *)content;

	ft_printf("flags = {%d}, token = {%s}\n", token->flags, token->token);
}

void		parse(char *line)
{
	int		i;

	i = 0;
	if (tokenize(line) == -1)
	{
		ft_printf("Error on parsing lines...");
		return;
	}

	// ft_lstmap(ms->tokens, &token_cmds, NULL);
	flags_tokens();
	ft_lstmap(ms->tokens, &print_tokens, NULL);
	// ft_lstclear(ms->tokens, free())
	return;
}


/*
	tokenize quotes/double quotes/backslash



*/
