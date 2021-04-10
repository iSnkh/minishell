/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:39:57 by wperu             #+#    #+#             */
/*   Updated: 2021/04/10 14:42:19 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_init_mshell(t_mshell *ms)
{
	int	i;

	ms->st_in = STDIN;
	ms->st_out = STDOUT;
	ms->st_err = STDERR;
	ms->ret = 0;
	ms->p = 0;
	ms->ext = 0;
	i = 0;
	if (ms->path)
		free(ms->path);
	ms->path = NULL;
}

int	ft_parse_redir_v2(char **cmd, t_mshell *ms)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], ">\0") == 0)
			ms->st_out = open(cmd[i + 1], O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (ft_strcmp(cmd[i], ">>\0") == 0)
			ms->st_out = open(cmd[i + 1], O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else if (ft_strcmp(cmd[i], "|"))
			ms->p = 1;
		/* else if (ft_strcmp(cmd[i],"<\0") == 0)
            if ((ms->st_in = open(cmd[i + 1],O_RDONLY)) < 0)
            {
                ft_printf("minishell: %s: No such file or directory\n", cmd[i +1]);
                return(-1);
            }*/
		i++;
	}
	return (1);
}

void	ft_clear_app(t_mshell *ms)
{
	ft_init_mshell(ms);
}
