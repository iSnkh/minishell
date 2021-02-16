/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:41:23 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/16 12:11:44 by amonteli         ###   ########lyon.fr   */
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

int		apply_slash(char *line, int index)
{
	int		flags;

	flags = 0;
	flags |= MS_SLASH;
	if (!line[index + 1])
		return (-1);
	add_char_token(line[index + 1], flags);
	return (1);
}

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

void	tokenize(char *line)
{
	int		count;
	int		ret;
	int		flags;

	count = 0;
	ret = 0;
	while (line[count])
	{
		if (line[count] == '\\')
		{
			if (apply_slash(line, count) == -1)
			{
				ft_printf("error\n");
				exit(-1); // TODO: HERE CLEAN EXIT
			}
			count += 1;
		}
		else if (line[count] == '\'')
		{
			ret = tokenize_quote(line + count + 1);
			if (ret < 0)
			{
				ft_printf("failed to read quotes\n");
				return;
			}
			count += ret;
		}
		else if (line[count] == '"')
		{
			ret = tokenize_dquote(line + count + 1);
			if (ret < 0)
			{
				ft_printf("failed to read quotes\n");
				return;
			}
			count += ret;
		}
		else
			add_char_token(line[count], 0);
		count++;
	}
}


/**
 * d'abord tokenizer les quotes et les flags
 * ensuite repasser dans tout les trucs pour virer les espaces/formatter
 * ensuite repasser encore pour replace chaque $XXXXXX par les variables d'env
*/
