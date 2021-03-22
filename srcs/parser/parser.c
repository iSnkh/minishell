/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/22 18:50:09 by amonteli         ###   ########lyon.fr   */
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
		if (!(tokenList->flags & MS_SLASH || tokenList->flags & MS_QUOTES || tokenList->flags & MS_DQUOTES))
		{
			if (!ft_strchr(tokenList->token, '\\'))
			{
				if (ft_strchr(tokenList->token, '>'))
				{
					// lst_append_after(lst, ft_lstnew(create_token("appended", 0)));
					t_list *lst2;
					lst2 = ft_lstnew(create_token("sa", 0));
					ft_lstadd_back(&lst2, ft_lstnew(create_token("lut", 0)));

					lst_append_lsts(lst, lst2);
				}
				if (ft_strchr(tokenList->token, '$'))
					replace_env(lst);
			}
		}
		lst = lst->next;
	}
}

void	*print_tokens(void *content)
{
	t_token	*token = (t_token *)content;

	ft_printf("[%d] {%s}\n", token->flags, token->token);
}

int		split_semi_colon(int splitter)
{

}

int		has_semi_colon()
{
	t_list	*list;
	t_token *tokenLst;
	int		semi_colons;
	int		count;

	semi_colons = 0;
	count = 0;
	list = ms->tokens;
	while (list)
	{
		tokenLst = (t_token *)list->content;
		if (!(tokenLst->flags & MS_SLASH || tokenLst->flags & MS_QUOTES || tokenLst->flags & MS_DQUOTES))
		{
			while (tokenLst->token[count])
			{
				if (tokenLst->token[count] == ';')
					semi_colons++;
				count++;
			}
		}
		list = list->next;
	}
	return (semi_colons);
}

void		parse(char *line)
{
	int		i;
	int		semi_colons;

	i = 0;
	semi_colons = 0;
	if (tokenize(line) == -1)
	{
		ft_printf("Error on parsing lines...");
		return;
	}
	semi_colons = has_semi_colon();
	if (!semi_colons)
		ms->cmds = ft_lstnew(ms->tokens); // no semi colons not need to split
	else
	{
		ft_printf("has %d semi colon inside! \n", semi_colons);
		// TODO: SPLIT HERE BY ';'
		// TODO: FLAGS TOKENS INSIDE ALL COMMANDS
		// TODO: ARGS[0] => COMMANDS
		// flags_tokens();
	}
	ft_lstmap(ms->tokens, &print_tokens, NULL);
	return;
}


/*
	tokenize quotes/double quotes/backslash



*/
