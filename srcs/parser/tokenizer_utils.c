/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 17:54:36 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/24 15:05:57 by amonteli         ###   ########lyon.fr   */
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

char	*dup_with_escaping(char *str, int size)
{
	char	*newstr;
	int		count;
	int		slash;

	count = 0;
	slash = 0;
	ft_printf("str={%s}\n", str);
	while (str[count] && count < size)
	{
		if (str[count] == '\\')
			slash++;
		count++;
	}
	newstr = ft_calloc(count, sizeof(char));
	ft_printf("count=%d\n", count);
	count = 0;
	slash = 0;
	while (str[count] && count < size)
	{
		if (str[count] != '\\')
		{
			newstr[slash] = str[count];
			slash++;
		}
		// ft_printf("s={%c},D={%c}\n", str[count], newstr[count]);
		count++;
	}
	ft_printf("str=%s\n", newstr);
	return (newstr);
}

int		fucking_slash(char *line, int flags)
{
	int		count;
	int		found;
	char	*str;

	count = 0;
	found = 0;
	while (line[count] && !found)
	{
		if (line[count] == '"')
			found = 1;
		if (line[count] == '"' && count > 0 && line[count - 1] == '\\')
			found = 0;
		ft_printf("%c", line[count]);
		count++;
	}
	if (!found)
		return (-1);
	ft_printf("\n");
	// str = dup_with_escaping(line, count - 1);
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
	flags |= MS_SLASH;
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
