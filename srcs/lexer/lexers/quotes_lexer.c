/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 02:27:23 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 08:38:52 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_status	lex_simple_quote(t_token **tokens, int flags)
{
	t_token		*str;
	char		*start;

	if (*ms->pos != '\'')
		return (LEXER_FNOMATCH);
	ms->pos++;
	start = ms->pos;
	while (*ms->pos && *ms->pos != '\'')
		ms->pos++;
	if (start == ms->pos || *ms->pos != '\'')
		return (LEXER_FSYNTAX);
	if (ms->pos != start)
	{
		str = ndup_token(start, ms->pos - start, T_SQUOTE | flags);
		if (!str)
			return (LEXER_FALLOC);
		token_add_back(tokens, str);
	}
	ms->pos++;
	return (LEXER_OK);
}

t_lexer_status	lex_backslash(t_token **tokens, int flags, char **start)
{
	t_token	*token;

	if (ms->pos != *start)
	{
		token = ndup_token(*start, ms->pos - *start, T_DQUOTE | flags);
		if (!token)
			return (LEXER_FALLOC);
		token_add_back(tokens, token);
	}
	if (!*++ms->pos)
		return (LEXER_FSYNTAX);
	token = ndup_token(ms->pos, 1, T_SQUOTE | flags);
	if (!token)
		return (LEXER_FALLOC);
	token_add_back(tokens, token);
	*start = ms->pos + 1;
	return (LEXER_OK);
}

t_lexer_status	lex_double_quote(t_token **tokens, int flags)
{
	t_lexer_status	status;
	t_token			*param;
	char			*start;

	status = LEXER_OK;
	if (*ms->pos != '"')
		return (LEXER_FNOMATCH);
	start = ++ms->pos;
	while (*ms->pos && *ms->pos != '"')
	{
		if (*ms->pos == '\\')
		{
			status = lex_backslash(tokens, flags, &start);
			if (status != LEXER_OK)
				return (status);
		}
		ms->pos++;
	}
	if (status != LEXER_OK)
		return (status);
	if (*ms->pos != '"')
		return (LEXER_FSYNTAX);
	param = ndup_token(start, ms->pos - start, T_DQUOTE | flags);
	if (!param)
		return (LEXER_FALLOC);
	token_add_back(tokens, param);
	ms->pos++;
	return (LEXER_OK);
}

t_lexer_status	lex_quotes(t_token **tokens, int flags)
{
	t_lexer_status	status;

	status = lex_double_quote(tokens, flags);
	if (status == LEXER_FNOMATCH)
		status = lex_simple_quote(tokens, flags);
	return (status);
}
