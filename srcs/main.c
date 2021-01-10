/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:28:20 by amonteli          #+#    #+#             */
/*   Updated: 2021/01/10 12:58:13 by amonteli         ###   ########lyon.fr   */
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
	line = ft_calloc(1, sizeof(char));
	ft_printf("\033[H\033[J");
	ft_printf("[minishell] >");

	cmd = ft_strdup("");
	while (get_next_line(1, &line))
	{
		printf("line={%s}\n", line);
		cmd = ft_strjoin(cmd, line);
		printf("cmd={%s}\n", cmd);
	}
}
