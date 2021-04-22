/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 02:57:00 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 08:50:41 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer_status	lex_cmd_simple(t_token **tokens)
{
	t_lexer_status	status;
	t_token			*inline_operators;
	t_token			*cmd_data;

	inline_operators = NULL;
	cmd_data = NULL;
	status = LEXER_OK;
	while (status == LEXER_OK && (status = lex_spaces()) == LEXER_OK)
		if ((status = lex_redirection(&inline_operators)) == LEXER_FNOMATCH)
		{
			status = lex_param(&cmd_data, T_PARAM);
			ft_printf("sl?=%s\n", cmd_data->data);
		}
	if ((inline_operators || cmd_data)
	&& (status = create_cmd(tokens, inline_operators, cmd_data)) != LEXER_OK)
	{
		clear_tokens(&inline_operators);
		clear_tokens(&cmd_data);
	}
	// while (status == LEXER_OK)
	// {
	// 	status = lex_spaces();
	// 	if (status != LEXER_OK)
	// 		break;
	// 	status = lex_redirection(&inline_operators);
	// 	if (status == LEXER_FNOMATCH)
	// 		status = lex_param(&cmd_data, T_PARAM);
	// }
	// if (inline_operators || cmd_data)
	// {
	// 	ft_printf("addy=%p, data=%s", inline_operators, (char *)cmd_data->data);
	// 	status = create_cmd(tokens, inline_operators, cmd_data);
	// 	if (status != LEXER_OK)
	// 	{
	// 		clear_tokens(&inline_operators);
	// 		clear_tokens(&cmd_data);
	// 	}
	// }
	return (status);
}