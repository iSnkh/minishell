/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:54:57 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/16 22:33:56 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		init_minishell(char **env)
{
	ms = malloc(sizeof(t_ms));
	(void)env;
	return (1);
}

void	minishell(int fd, char *line, char **env)
{
	(void)fd;
	if (!init_minishell(env))
		return perror("Failed to init Minishell");
	ft_printf("[Debug] line=[%s]\n", line);
}

int		main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	clear_console();
	minishell(0, argv[1], env);
	return (0);
}