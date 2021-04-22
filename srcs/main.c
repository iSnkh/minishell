/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:54:57 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 08:35:37 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_minishell(char **env)
{
	ms = malloc(sizeof(t_ms));
	ms->count = 0;
	ms->line = NULL;
	ms->line_len = 0;
	ms->pos = NULL;
	ms->lex_status = -100;
	(void)env;
	return (1);
}

void	print_error(int status_code)
{
	if (status_code == CHECKER_SLASH || status_code == UNCOMPLETED_DQUOTE || status_code == UNCOMPLETED_QUOTE)
		ft_printf("[Error] Multiligne is not supported!\n");
}

void	debug_print(t_token *tokens)
{
	t_token	*current;

	// current = *tokens;
	ft_printf("\n\n\n");
	while ((current = tokens))
	{
		// current = *tokens;
		// if (current->type == T_CMD)
		// {
		// 	ft_printf("data={%d}\n", current->type);
		// 	// current = current->next;
		// }
		ft_printf("data={%s} - type={%d}\n", current->data, current->type);
		tokens = current->next;
	}
}

void	shell_loop()
{
	t_token			*tokens;
	t_lexer_status	status;
	char			*line;
	int				ret;
	line = ft_calloc(1, sizeof(char));

	tokens = NULL;
	while (get_next_line(0, &line))
	{
		// ret = check_line_input(line);
		ms->pos = line;
		status = lex_tokens(&tokens);
		debug_print((t_token *)tokens->data);
		ft_printf("[seith@minishell] >");
	}
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	clear_console();
	init_minishell(env);
	ft_printf("[seith@minishell] >");
	shell_loop();
	return (0);
}