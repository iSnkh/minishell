/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:28:20 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/23 17:19:32 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_struct(char **env)
{
	ms = malloc(sizeof(t_ms));
	if (!ms)
	{
		printf("ERROR TO MALLOC");
		return ;
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
	(void)args;
	if (argc != 1)
		printf("error please call ./minishell");
	minishell(env);
	printf("argc=%d\n", argc);
}
