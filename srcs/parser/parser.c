/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/24 17:50:26 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*print_tokens(void *content)
{
	t_token	*token = (t_token *)content;

	ft_printf("[%d] {%s}\n", token->flags, token->token);
}

void	*print_commands(void *content)
{
	t_cmd	*cmd = (t_cmd *)content;

	if (cmd->flags & CMD_PARSED)
	{
		ft_printf("=========-[%s]-=========\n", cmd->cmd_name);
		ft_printf(">> Flags = [%d]\n", cmd->flags);
		ft_lstmap(cmd->args, &print_tokens, NULL);
		ft_printf("========================\n");
	}
	else
	{
		ft_printf("=========-[Unknown]-=========\n");
		ft_printf(">> Flags = [%d]\n", cmd->flags);
		ft_lstmap(cmd->args, &print_tokens, NULL);
		ft_printf("========================\n");
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
		if (!is_escaped(tokenList))
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


int		split_semi_colon(int splitter)
{
	t_list	*list;
	t_cmd	*cmd;
	t_token *token;

	cmd = create_cmd(NULL);
	cmd->flags = 0;
	list = ms->tokens;
	while (list)
	{
		token = (t_token *)list->content;
		if (is_escaped(token))
		{
			ft_lstadd_back(&cmd->args, ft_lstnew(create_token(token->token, token->flags)));
		}
		else
		{

		}

		list = list->next;
	}

	ms->cmds = ft_lstnew(cmd);
}

/**
 * 	while token
 * 	if
 *
 */

int		count_seps()
{
	t_list	*list;
	t_token *tokenLst;
	int		separators;
	int		count;

	separators = 0;
	list = ms->tokens;
	while (list)
	{
		tokenLst = (t_token *)list->content;
		if (!is_escaped(tokenLst))
		{
			count = 0;
			while (tokenLst->token[count])
			{
				if (tokenLst->token[count] == '>')
				{
					if (tokenLst->token[count + 1] && tokenLst->token[count + 1] == '>')
						count++;
					separators++;
				}
				if (tokenLst->token[count] == '<')
					separators++;
				if (tokenLst->token[count] == '|')
					separators++;
				if (tokenLst->token[count] == ';')
					separators++;
				if (tokenLst->token[count] == '<')
					separators++;
				count++;
			}
		}
		list = list->next;
	}
	return (separators);
}

void		parse(char *line)
{
	int		i;
	int		separators;

	i = 0;
	if (tokenize(line) == -1)
	{
		ft_printf("Error on parsing lines...");
		return;
	}
	separators = count_seps();
	if (!separators)
		ms->cmds = ft_lstnew(create_cmd(ms->tokens)); // no semi colons not need to split
	else
	{
		split_into_commands(separators);
		// split_semi_colon(separators);
		// TODO: SPLIT HERE BY ';'
		// TODO: FLAGS TOKENS INSIDE ALL COMMANDS
		// TODO: ARGS[0] => COMMANDS
		// flags_tokens();
	}
	ft_lstmap(ms->cmds, &print_commands, NULL);
	return;
}


/*
	tokenize quotes/double quotes/backslash
	split by commands


*/
