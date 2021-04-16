/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:54:36 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/08 11:33:38 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		tokenize_quote(char *line)
{
	int		count;
	int		flags;
	char	*str;

	flags = 0;
	flags |= MS_QUOTES;
	if (!ft_strchr(line, '\'') )
		return (-1);
	count = ft_strchr(line, '\'') - (line);
	str = ft_substr(line, 0, count);
	if (ft_strlen(str) > 0)
		ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(str, flags)));
	return (count + 2);
}

int		fucking_slash(char *line, int flags)	// TODO: BORDEL DE MERDE POURQUOI TU DECONNE SLASH DE MORT.
{
	int		count;
	int		found;
	char	*str;

	count = 0;
	found = 0;
	while (line[count] && !found)
	{
		if (line[count] == '\\')
			count += 2;
		else if (line[count] == '"')
		{
			found = 1;
			count++;
		}
		else
			count++;
	}
	if (!found)
		return (-1);
	str = ft_strndup(line, count - 1);
	if (ft_strlen(str) > 0)
		ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(str, flags)));
	return (count + 1);
}

int		tokenize_dquote(char *line)
{
	int		count;
	int		flags;
	char	*str;

	flags = 0;
	flags |= MS_DQUOTES;
	if (!ft_strchr(line, '"'))
		return (-1);
	if (!ft_strchr(line, '\\'))
	{
		count = ft_strchr(line, '"') - (line);
		str = ft_substr(line, 0, count);
		if (ft_strlen(str) > 0)
			ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(str, flags)));
		return (count + 2);
	}
	return (fucking_slash(line, flags));
}


int		has_to_tokenize(char *line)
{
	if (ft_strrchr(line, '\\'))
		return (1);
	if (ft_strchr(line, '\''))
		return (1);
	if (ft_strchr(line, '"'))
		return (1);
	return (0);
}

int		get_len_to_token(char *line)
{
	int		count;

	count = 0;
	while (line[count])
	{
		if (line[count] == '\\' || line[count] == '\'' || line[count] == '"')
			return (count);
		count++;
	}
	return (-1);
}
