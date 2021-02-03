/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/03 10:42:22 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void 	*lstmap_f(void *content)
{
	t_cmd	*cmd = (t_cmd*)content;
	// ft_printf("cmd = {%s}\n", cmd->cmd);
}

void	*format_tokens(void *content)
{
	t_token	*token = (t_token *)content;


}

void	*print_tokens(void *content)
{
	t_token	*token = (t_token *)content;

	ft_printf("token = {%s}\n", token->token);
}

void		parse(char *line)
{
	char	**cmds;
	int		i;

	i = 0;
	tokenize(line);
	ft_lstmap(ms->tokens, &print_tokens, NULL);
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


// dans le cas ou j'ai '\'' y'a deux quotes le truc c'est que y'en a trois donc il faut que je check un avant
// si jamais c'est un backslash ou pas et si c'est un backslash remove le flag
