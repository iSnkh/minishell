/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:03:28 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/08 18:15:14 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_replace_env(t_cmd *cmd)
{
	t_list	*list;
	t_token	*token;
	int		count;

	list = cmd->args;
	while (list)
	{
		token = (t_token *)list->content;
		while (ft_strchr(token->token, '$') && !(token->flags & MS_SLASH || token->flags & MS_QUOTES))
		{
			replace_env(list);
		}
		list = list->next;
	}
}

void	cmd_replace_slash(t_cmd *cmd)
{
	t_list	*list;
	t_token	*token;
	char	*str;
	int		count;
	int		effect;

	list = cmd->args;
	while (list)
	{
		token = (t_token *)list->content;
		if (ft_strchr(token->token, '\\') && !(token->flags & MS_SLASH || token->flags & MS_QUOTES))
		{
			if (ft_strchr(DQUOTE_EFFECT, ft_strchr(token->token, '\\')[1]))
				effect = 1;
			else
				effect = 0;
			ft_printf("token=[%s], char=[%c], effect=[%d]\n", token->token, ft_strchr(token->token, '\\')[1], effect);
			if (effect)
			{
				str = ft_strremove(token->token, '\\');
				ft_printf("str={%s}\n", str);
				token->token = ft_strdup(str);
				free(str);
			}
		}
		list = list->next;
	}
}

void	format_commands(void)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = ms->cmds;
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;
		cmd_replace_slash(cmd);
		// cmd_replace_env(cmd);
		// cmd_replace_slash(cmd);
		//	FORMAT SPACES
		//	SET ARG 0 TO CMD NAME & SET FLAG PARSED
		//	EXEC

		cmds = cmds->next;
	}
	ft_lstmap(ms->cmds, &print_commands, NULL);
}

