/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 02:19:26 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 08:52:52 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_special(char c)
{
	return (ft_strchr(LEXER_SPEC, c) != NULL);
}

t_lexer_status	lex_param_simple(t_token **tokens, int flags)
{
	t_token		*token;
	char		*start;

	start = ms->pos;
	while (*ms->pos && !is_special(*ms->pos))
		ms->pos++;
	// ft_printf("[param_LEXER] start=%s, pos=%s\n", start, ms->pos);
	// ft_printf("[param_LEXER] start=%p, pos=%p, subed=%p\n", start, ms->pos, ms->pos - start);
	if (ms->pos == start)
		return (LEXER_FNOMATCH);
	// ft_printf("has matched...");
	// ft_printf("added new={%s}\n", (char *)((int)(ms->pos - start)));
	token = ndup_token(start, ms->pos - start, T_SIMPLE | flags);
	// ft_printf("token out={%s}\n", (char *)token->data);
	if (!token)
		return (LEXER_FALLOC);
	token_add_back(tokens, token);
	return (LEXER_OK);
}

t_lexer_status	lex_param(t_token **tokens, int flags)
{
	t_lexer_status	status;
	t_token			*param;
	t_token			*param_data;

	param_data = NULL;
	status = LEXER_OK;
	while (status == LEXER_OK)
		if ((status = lex_quotes(&param_data, flags)) == LEXER_FNOMATCH)
			status = lex_param_simple(&param_data, flags);
	// ft_printf("lex data=%s\n", (char *)param_data->data);
	if (param_data && status == LEXER_FNOMATCH)
	{
		param = new_token(param_data, flags);
		if (param)
		{
			token_add_back(tokens, param);
			status = LEXER_OK;
		}
		else
			status = LEXER_FALLOC;
	}
	if (status != LEXER_OK)
		clear_tokens(&param_data);
	return (status);
}
