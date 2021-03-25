/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 19:03:28 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/25 19:14:59 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	cmd_replace_env(t_cmd *cmd)
{
	t_list	*list;
	t_token	*token;

	list = cmd->args;
	while (list)
	{
		token = (t_token *)list->content;
		if (ft_strchr(token->token, '$') && !(token->flags & MS_SLASH || token->flags & MS_QUOTES))
		{

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
		cmd_replace_env(cmd);
		//	FORMAT SPACES
		//	SET ARG 0 TO CMD NAME & SET FLAG PARSED
		//	EXEC

		cmds = cmds->next;
	}
}

