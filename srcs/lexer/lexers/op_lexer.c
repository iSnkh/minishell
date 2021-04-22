/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 05:23:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/21 05:29:16 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_status			lex_operator(t_token **tokens)
{
	int		type;
	t_token	*operator;

	if (*ms->pos == '|')
	{
		type = OP_PIPE;
		ms->pos++;
	}
	else
		return (LEXER_FNOMATCH);
	operator = new_token(NULL, type);
	if (!operator)
		return (LEXER_FALLOC);
	token_add_back(tokens, operator);
	return (LEXER_OK);
}

t_lexer_status			lex_operation(t_token **tokens)
{
	t_lexer_status	status;

	status = lex_operator(tokens);
	if (status != LEXER_OK)
		return (status);
	status = lex_spaces();
	if (status == LEXER_OK)
		status = lex_cmd_simple(tokens);
	return (status);
}
