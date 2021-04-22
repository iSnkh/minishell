/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_lexer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 05:03:22 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 08:44:34 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_type(void)
{
	int		type;

	type = FALSE;
	if (*ms->pos == '>')
	{
		ms->pos++;
		if (*ms->pos == '>')
		{
			type = OP_DREDIR;
			ms->pos++;
		}
		else
			type = OP_RREDIR;
	}
	else if (*ms->pos == '<')
	{
		type = OP_LREDIR;
		ms->pos++;
	}
	return (type);
}

t_lexer_status	lex_redirection(t_token **tokens)
{
	const int		type = get_redir_type();
	t_lexer_status	status;
	t_token			*redir;
	t_token			*redir_data;

	redir_data = NULL;
	if (type == FALSE)
		status = LEXER_FNOMATCH;
	else if (lex_spaces() != LEXER_OK || (status = lex_param(&redir_data, T_PARAM)) == LEXER_FNOMATCH)
		status = LEXER_FSYNTAX;

	// else if (lex_spaces() != LEXER_OK) // TODO: check douteux ca :/ 
	// {
	// 	status = lex_param(&redir_data, T_PARAM);
	// 	if (status == LEXER_FNOMATCH)
	// 		status = LEXER_FSYNTAX;
	// }
	else if (status == LEXER_OK)
	{
		redir = new_token(redir_data, type);
		if (!redir)
		{
			clear_tokens(&redir_data);
			status = LEXER_FALLOC;
		}
		else
			token_add_back(tokens, redir);
	}
	return (status);
}
