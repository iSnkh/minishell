/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 22:37:23 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 08:57:38 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_status			lex_tokens(t_token **tokens)
{
	t_lexer_status	status;

	while ((status = lex_spaces()) == LEXER_OK
	&& (status = lex_token(tokens)) == LEXER_OK
	&& (status = lex_spaces()) == LEXER_OK
	&& (status = lex_separator(tokens)) == LEXER_OK)
		;
	ft_printf("lexer_status={%d}\n", status);
	if (status == LEXER_FNOMATCH)
		status = LEXER_FSYNTAX;
	else if (status == LEXER_END)
		status = LEXER_OK;
	return (status);
}


t_lexer_status	lexefcedx_tokens(t_token **tokens)
{
	int	status;

	status = LEXER_OK;
	ft_printf("{%s}\n", ms->pos);
	while (status == LEXER_OK)
	{
		status = lex_spaces();
		if (status != LEXER_OK)
			break;
		status = lex_token(tokens);
		if (status != LEXER_OK)
			break;
		status = lex_spaces();
		if (status != LEXER_OK)
			break;
		status = lex_separator(tokens);
	}
	ft_printf("lexer_status={%d}\n", status);
	if (status == LEXER_FNOMATCH)
		status = LEXER_FSYNTAX;
	if (status == LEXER_END)
	{
		status = LEXER_OK;
	}
	ft_printf("{%s}\n", ms->pos);
	return (status);
		// ft_printf("end of the line...\n");
	// ft_printf("ended proccess\n");
}