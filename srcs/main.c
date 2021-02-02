/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:28:20 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/02 14:28:43 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(char **env)
{
	if (!(ms = malloc(sizeof(t_ms))))
	{
		// TODO: clean exit
		printf("ERROR TO MALLOC");
		return;
	}
	ms = malloc(sizeof(t_ms));
	ms->env = env;
	ms->cmds = NULL;
	ms->tokens = NULL;
}

void	minishell(char **env)
{
	init_struct(env);
	clear_console();
	ft_printf("[minishell] >");
	shell_loop();
}

int		main(int argc, char **args, char **env)
{
	if (argc != 1)
		printf("error please call ./minishell");
	minishell(env);
	printf("argc=%d\n", argc);
}
