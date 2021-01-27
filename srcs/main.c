/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:28:20 by amonteli          #+#    #+#             */
/*   Updated: 2021/01/27 16:50:15 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **args, char **env)
{
	// ft_printf("argc: %d", argc);

	// int i;
	// while (env[i])
		// ft_printf("{%s}\n", env[i++]);

	char *line;
	char *cmd;
	int ret;

	ret = 0;
	init_shell(argc, args, env);
	shell_loop(0, env);
}
