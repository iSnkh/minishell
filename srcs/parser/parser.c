/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/24 11:36:19 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	ft_lstmap(ms->tokens, &print_tokens, NULL);
	// ft_lstclear(ms->tokens, free())
	return;


	// if (!(cmds = split_cmds(line)))
	// 	ft_printf("parse error!");
	// while (cmds[i])
	// {
	// 	parse_command(cmds[i]);
	// 	ft_lstadd_back(&ms->cmds, ft_lstnew(create_cmd(cmds[i])));
	// 	i++;
	// }
	// ft_lstmap(ms->cmds, &lstmap_f, NULL);
}
