/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/02 17:27:47 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: CLEAN THIS SHIT
int		tokenize_quote(char *line)
{
	int		count;
	int		flags;
	char	*str;

	flags = 0;
	flags |= MS_QUOTES;
	if (!ft_strchr(line, '\''))
	{
		// TODO: ERROR
		ft_printf("error invaldi quotes");
		exit(-1);
	}
	count = ft_strchr(line, '\'') - (line);
	str = ft_substr(line, 0, count);
	ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(str, flags)));
	return (count + 1);
}

void	tokenize(char *line)
{
	int		i;
	int		flags;

	i = 0;
	flags = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i += tokenize_quote(line + i + 1);
		}
		i++;
	}
}

void 	*lstmap_f(void *content)
{
	t_cmd	*cmd = (t_cmd*)content;
	// ft_printf("cmd = {%s}\n", cmd->cmd);
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
