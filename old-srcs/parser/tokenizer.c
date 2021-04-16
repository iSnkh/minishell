/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:41:23 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/06 16:10:08 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(char *token, int size, int flags)
{
	ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(ft_strndup(token, size), flags)));
}

void	add_char_token(char token, int flags)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = token;
	ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(str, flags)));
}

int		apply_slash(char *line)
{
	int		flags;

	flags = 0;
	flags |= MS_SLASH;
	if (!(line[1]))
		return (-1);
	add_char_token(line[1], flags);
	return (1);
}

int		tokenize(char *line)
{
	int		ret;

	ret = 0;
	if (!has_to_tokenize(line) && ft_strlen(line) > 0)
	{
		ft_lstadd_back(&ms->tokens, ft_lstnew(create_token(line, 0)));
		return (1);
	}
	while(has_to_tokenize(line))
	{
		if (ft_strlen(line) > 0 && get_len_to_token(line) > 0 && get_len_to_token(line) != -1)
			add_token(line, get_len_to_token(line), 0);
		line = line + get_len_to_token(line);
		if (*line == '\\')
		{
			if (apply_slash(line) == -1)
				ft_printf("error backslash\n");
			line += 2;
		}
		else if (*line == '\'')
		{
			ret = tokenize_quote(line + 1);
			if (ret < 0)
			{
				ft_printf("failed to read quotes\n");
				return (-1);
			}
			line += ret;
		}
		else if (*line == '"')
		{
			ret = tokenize_dquote(line + 1);
			if (ret < 0)
			{
				ft_printf("failed to read doubles quotes\n");
				return (-1);
			}
			line += ret;
		}
	}
	if (ft_strlen(line) > 0)
		add_token(line, ft_strlen(line), 0);
	return (1);
}

/**
 * d'abord tokenizer les quotes et les flags
 * ensuite repasser dans tout les trucs pour virer les espaces/formatter
 * ensuite repasser encore pour replace chaque $XXXXXX par les variables d'env
*/
