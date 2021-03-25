/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 18:33:57 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/25 19:05:23 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(void)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = ms->cmds;
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;


		cmds = cmds->next;
	}
}
