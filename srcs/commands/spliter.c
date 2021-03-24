/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:40:18 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/24 19:00:16 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		_split_semi_colon(int splitter)
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

int		containing_separator(char *str)
{
	int		count;

	count = 0;
	while (str[count])
	{
		if (is_cmd_sep(str[count]))
			return (1);
		count++;
	}
	return (0);
}

char	*get_spliter_pos(char *str)
{
	int	count;

	count = 0;
	while (str[count])
	{
		if (is_cmd_sep(str[count]))
			return (str + count);
		count++;
	}
	return (-1);
}

// int		sep_

t_cmd	*cut_around_spliter(t_cmd *cmd, t_token *token, int *separators)
{
	t_cmd	*new;
	char	*str;
	char	*type;
	int		count;

	new = create_cmd(NULL);
	type = get_spliter_pos(token->token);
	str = ft_substr(token->token, 0, type - token->token);
	ft_printf("str={%s}, type={%c}\n", str, *type);
	// TODO: need to do the function that transform char to flag
	// ft_printf("token=%p, type=%p, str={%d} type =%c\n", token->token, type, type - token->token, *type);
	return (NULL);
}

int		split_into_commands(int separators)
{
	t_list	*list;
	t_cmd	*cmd;
	t_token *token;

	ft_printf("\n\n[Debug] Separators=%d, Commands=%d\n", separators, separators + 1);
	cmd = create_cmd(NULL);
	list = ms->tokens;
	while (list && separators)
	{
		token = (t_token *)list->content;
		if (is_escaped(token))
			ft_lstadd_back(&cmd->args, ft_lstnew(create_token(token->token, token->flags)));
		else
		{
			if (containing_separator(token->token))
			{
				cmd = cut_around_spliter(cmd, token, &separators);
			}
		}
		list = list->next;
	}
}


/**
 * 	tant que je peux explorer et que je sais que y'a commands j'explore
 *  jusqu'a la commande je add les tokens
 *  quand je croise un token qui contient le truc je passe la command en args et il decoupe AVANT**SEPARATOR**APRES DANS LE TOKEN dans la commande
 * 	--separators;
 * 	il continue jusqu'au prochain
 *	une fois qu'il n'y a plus de separators il add les tokens a la fin
 */
