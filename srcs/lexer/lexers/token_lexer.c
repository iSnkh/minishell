/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 00:26:52 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 01:54:56 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_status	lex_token(t_token **tokens)
{
	t_lexer_status	status;

	status = lex_cmd_simple(tokens);
	if (status == LEXER_OK)
	{
		while (status == LEXER_OK)
		{
			status = lex_spaces();
			if (status != LEXER_OK)
				break;
			status = lex_operation(tokens);
		}
		if (status == LEXER_FNOMATCH)
			status = LEXER_OK;
	}
	return (status);
}
