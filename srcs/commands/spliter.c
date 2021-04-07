/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:40:18 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/07 11:37:57 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	containing_separator(char *str)
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
	return (NULL);
}

int	type_to_flag(char *type)
{
	if (type[0] == '>' && type[1] && type[1] == '>')
		return (CMD_DREDIR);
	if (type[0] == '>')
		return (CMD_RREDIR);
	if (type[0] == '<')
		return (CMD_LREDIR);
	if (type[0] == ';')
		return (CMD_SEP);
	if (type[0] == '|')
		return (CMD_PIPE);
	return (-1);
}

t_cmd	*cut_around_spliter(t_cmd *cmd, t_token *token)
{
	t_cmd	*new;
	char	*str;
	char	*type;

	new = create_cmd(NULL);
	type = get_spliter_pos(token->token);
	str = ft_substr(token->token, 0, type - token->token);
	cmd->flags |= type_to_flag(type);
	ft_lstadd_back(&cmd->args, ft_lstnew(create_token(str, 0)));
	ft_lstadd_back(&ms->cmds, ft_lstnew(cmd));
	str = ft_strdup(token->token + (type - token->token) + 1);
	free(token->token);
	token->token = str;
	return (new);
}

void	split_into_commands(void)
{
	t_list	*list;
	t_cmd	*cmd;
	t_token	*token;

	cmd = create_cmd(NULL);
	list = ms->tokens;
	while (list)
	{
		token = (t_token *)list->content;
		if (is_escaped(token))
			ft_lstadd_back(&cmd->args,
				ft_lstnew(create_token(token->token, token->flags)));
		else
		{
			while (containing_separator(token->token))
				cmd = cut_around_spliter(cmd, token);
			if (ft_strlen(token->token) > 0)
				ft_lstadd_back(&cmd->args,
					ft_lstnew(create_token(token->token, token->flags)));
		}
		list = list->next;
	}
	ft_lstadd_back(&ms->cmds, ft_lstnew(cmd));
}
