/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:41:23 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/03 13:32:56 by amonteli         ###   ########lyon.fr   */
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
	if (!ft_strchr(line, '\''))
		return (-1);
	count = ft_strchr(line, '\'') - (line);
	str = ft_substr(line, 0, count);
	if (ft_strlen(str))
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
	count = ft_strchr(line, '"') - (line);
	str = ft_substr(line, 0, count);
	if (ft_strlen(str))
		ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(str, flags)));
	return (count + 1);
}

void	tokenizeefws(char *line)
{
	int		i;
	int		istr;
	int		ret;
	char	*str;

	i = 0;
	istr = 0;
	str = calloc(sizeof(char), ft_strlen(line));
	while (line[i])
	{
		if (line[i] == '\'')
		{
			ret = tokenize_quote(line + i + 1);
			if (ret < 0)
			{
				ft_printf("failed to read quotes\n");
				return;
			}
			i = i + ret + 1;
		}
		if (line[i] == '"')
		{
			ret = tokenize_dquote(line + i + 1);
			if (ret < 0)
			{
				ft_printf("failed to read quotes\n");
				return;
			}
			i = i + ret + 1;
		}
		else if (line[i])
		{
			str[istr] = line[i];
			i++;
		}
	}
}

int		found_escape_char(char *line)
{
	if (ft_strchr(line, '\\')) // has backslash
	{
		if (*line + 1 != '\0' && (*line + 1 == '\'' || *line + 1 == '"'))
			return (0);
	}
	if (ft_strchr(line, '\'')) // has quote
	{
		return (1);
	}
	if (ft_strchr(line, '"'))
	{
		return (1);
	}
	return (0);
}

int		jump_to_escaped_char(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			return (i);
		i++;
	}
	return (-1);
}

void	tokenize(char *line)
{
	// one token if all doesn't contains escape char
	if (!ft_strchr(line, '\'') && !ft_strchr(line, '"') && !ft_strchr(line, '\\'))
		return (ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(ft_strdup(line), 0))));

	// while token found like ' " \ loop
	while(found_escape_char(line))
	{
		ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(ft_strndup(line, ft_strchr_len(line, '\'')), 0)));
		ft_printf("found escaped token ");
		ft_printf("found at %d\n", jump_to_escaped_char(line));
		line = line + jump_to_escaped_char(line) + 1;
	}
}


/**
 * d'abord tokenizer les quotes et les flags
 * ensuite repasser dans tout les trucs pour virer les espaces/formatter
 * ensuite repasser encore pour replace chaque $XXXXXX par les variables d'env
*/
