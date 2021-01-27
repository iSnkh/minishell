/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:45:10 by amonteli          #+#    #+#             */
/*   Updated: 2021/01/27 16:50:06 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(int args_count, char **args, char **env)
{
	clear_console();
	ft_printf("[minishell] >");
}

void	shell_loop(t_ms *ms, char **env)
{
	char	*line;

	line = ft_calloc(1, sizeof(char));
	while (get_next_line(0, &line))
	{
		parse(env, line);
		printf("line={%s}\n", line);
		// cmd = ft_strjoin(cmd, line);
		// printf("cmd={%s}\n", cmd);
	}
}
