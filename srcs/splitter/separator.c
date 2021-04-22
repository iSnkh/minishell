/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 22:40:46 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/17 18:37:50 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		skip_quotes(char *line)
{
	int		found;
	char	type;

	found = 0;
	type = line[ms->count];
	ms->count++;
	while (line[ms->count])
	{
		ft_printf("%c", line[ms->count]);
		if (line[ms->count] == '\\')
			ms->count += 2;
		else if (line[ms->count] == type)
		{
			ms->count++;
			return (1);
		}
		else
			ms->count++;
	}
	if (type == '"')
		return (UNCOMPLETED_DQUOTE);
	else 
		return (UNCOMPLETED_QUOTE);
}

int		fetch_command(char *line)
{
	int		ret;

	while (line[ms->count] && line[ms->count] != ';')
	{
		if (line[ms->count] == '\\')
			ms->count += 2;
		else if (line[ms->count] == '"' || line[ms->count] == '\'')
		{
			ret = skip_quotes(line);
			if (ret < 0)
				return (ret);
		}
		else
			ms->count++;
	}
	ms->line = ft_strndup(line, ms->count);
	ms->line_len = (int)ft_strlen(ms->line);
	ms->pos = line;
	return (TRUE);
}
