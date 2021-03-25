/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:40:18 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/25 16:15:47 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (NULL);
}

int		type_to_flag(char *type)
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
	if (cmd->flags & CMD_DREDIR)
		str = ft_strdup(token->token + (type - token->token) + 2);
	else
		str = ft_strdup(token->token + (type - token->token) + 1);
	free(token->token);
	token->token = str;
	return (new);
}

int		split_into_commands(int separators)
{
	t_list	*list;
	t_cmd	*cmd;
	t_token *token;

	ft_printf("\n\n[Debug] Separators=%d, Commands=%d\n", separators, separators + 1);
	cmd = create_cmd(NULL);
	list = ms->tokens;
	while (list)
	{
		token = (t_token *)list->content;
		if (is_escaped(token))
			ft_lstadd_back(&cmd->args, ft_lstnew(create_token(token->token, token->flags)));
		else
		{
			while (containing_separator(token->token))
				cmd = cut_around_spliter(cmd, token);
			if (ft_strlen(token->token) > 0)
				ft_lstadd_back(&cmd->args, ft_lstnew(create_token(token->token, token->flags)));
		}
		list = list->next;
	}
	ft_lstadd_back(&ms->cmds, ft_lstnew(cmd));
}


/**
 * 	tant que je peux explorer et que je sais que y'a commands j'explore
 *  jusqu'a la commande je add les tokens
 *  quand je croise un token qui contient le truc je passe la command en args et il decoupe AVANT**SEPARATOR**APRES DANS LE TOKEN dans la commande
 * 	--separators;
 * 	il continue jusqu'au prochain
 *	une fois qu'il n'y a plus de separators il add les tokens a la fin
 */
