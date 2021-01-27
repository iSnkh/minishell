/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:43:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/01/27 17:25:54 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			parser_check_quotes(char *line)
{
	int		i;
	int		flags;

	i = 0;
	flags = 0;
	while(line[i])
	{
		// check simple quotes
		if (line[i] == '\'')
		{
			if (!(flags & MS_QUOTES))
			{
				// check i - 1 != SEGFAULT puis check si i - 1 == \ alors je la compte pas
				if (i > 0 && line[i - 1] == '\\')
					break;
				flags |= MS_QUOTES;
			}
			else
				flags &= ~MS_QUOTES;
		}

		// check doubles quotes
		if (line[i] == '\"')
		{
			if (flags & MS_DQUOTES)
				flags &= ~MS_DQUOTES;
			else
				flags |= MS_DQUOTES;
		}
		i++;
	}
	if (flags & MS_QUOTES || flags & MS_DQUOTES)
		printf("invalid quotes number...");
	return (1);
}

void		parse(char **env, char *line)
{
	printf("{%s}\n", line);
	if (!(parser_check_quotes(line)))
	{
		perror("Uncompleted quotes.");
	}
}


// dans le cas ou j'ai '\'' y'a deux quotes le truc c'est que y'en a trois donc il faut que je check un avant
// si jamais c'est un backslash ou pas et si c'est un backslash remove le flag
