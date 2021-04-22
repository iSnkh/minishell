/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 23:20:38 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 08:27:28 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_line_input(char *line)
{
	return (1);
	if (line[ft_strlen(line) - 1] == '\\')
		return (CHECKER_SLASH);
	return (1);
}
