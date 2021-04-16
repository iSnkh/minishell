/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 15:56:33 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/30 15:56:51 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*print_tokens(void *content)
{
	t_token	*token = (t_token *)content;

	ft_printf("[%d] {%s}\n", token->flags, token->token);
	return (NULL);
}

void	*print_commands(void *content)
{
	t_cmd	*cmd = (t_cmd *)content;

	if (cmd->flags & CMD_PARSED)
	{
		ft_printf("\n=========-[%s]-=========\n", cmd->cmd_name);
		ft_printf(">> Flags = [%d]\n", cmd->flags);
		ft_lstmap(cmd->args, &print_tokens, NULL);
		ft_printf("========================\n");
	}
	else
	{
		ft_printf("\n=========-[Unknown]-=========\n");
		ft_printf(">> Flags = [%d]\n", cmd->flags);
		ft_lstmap(cmd->args, &print_tokens, NULL);
		ft_printf("========================\n");
	}
	return (NULL);
}
