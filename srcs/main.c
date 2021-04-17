/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:54:57 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/17 15:56:08 by amonteli         ###   ########lyon.fr   */
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
	(void)env;
	return (1);
}

void	print_error(int status_code)
{
	if (status_code == CHECKER_SLASH || status_code == UNCOMPLETED_DQUOTE || status_code == UNCOMPLETED_QUOTE)
		ft_printf("[Error] Multiligne is not supported!\n");
	// if (status_code == UNCOMPLETED_QUOTE)

}

void	shell_loop()
{
	char	*line;
	int		ret;
	line = ft_calloc(1, sizeof(char));

	ft_printf("[seith@minishell] >");
	while (get_next_line(0, &line))
	{
		ret = check_line_input(line);
		if (ret > 0)
		{
			ft_printf("[DEBUG] line=[%s]\n", line);
			ret = fetch_command(line);
			if (ret > 0)
			{
				ft_printf("[DEBUG] ms_line=[%s], len=[%d]\n", ms->line, ms->line_len);

			}
			else 
				print_error(ret);
		}
		else
			print_error(ret);
		ft_printf("[seith@minishell] >");
	}
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	clear_console();
	// ft_printf("[seith] >");
	init_minishell(env);
	shell_loop();
	return (0);
}