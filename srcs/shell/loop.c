/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:45:10 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/18 17:59:13 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(void)
{
	char	*line;

	line = ft_calloc(1, sizeof(char));
	while (get_next_line(0, &line))
	{
		parse(line);
		// exec
		// clear tokens
		ft_printf("[minishell] >");

		// ft_printf("wesh?");
	}
}
