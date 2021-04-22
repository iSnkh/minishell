/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 05:34:58 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 01:54:25 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_status	lex_separator(t_token **tokens)
{
	t_lexer_status	status;
	t_token			*sep;

	if (*ms->pos == '\0')
		status = LEXER_END;
	else if (*ms->pos != '\0' && *ms->pos == ';')
	{
		ms->pos++;
		sep = new_token(NULL, T_SEP);
		token_add_back(tokens, sep);
		return (LEXER_OK);
	}
	else
		status = LEXER_FNOMATCH;
	return (status);
}