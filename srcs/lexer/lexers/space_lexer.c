/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 00:34:26 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/21 05:12:33 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 	is a spaces?
 */

int	is_spaces(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

/**
 * skip white spaces
 */

t_lexer_status	lex_spaces(void)
{
	while (is_spaces(*ms->pos))
		ms->pos++;
	if (*ms->pos == '\0')
		return (LEXER_END);
	return (LEXER_OK);
}
