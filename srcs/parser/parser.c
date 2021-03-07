/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/07 18:00:57 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_replace(t_list *current, t_list *list)
{
	t_list	*next;

	if (!current || !list)
		return;
	if (!current->next)
	{
		current->next = list;
		return;
	}

}

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
				if (ft_strchr(tokenList->token, '>'))
				{
					lst_replace(lst, ft_lstnew(create_token("replaced", 0)));
					ft_printf("hello\n");
				}
			}
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
