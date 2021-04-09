/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:08:19 by wperu             #+#    #+#             */
/*   Updated: 2021/04/09 15:33:29 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_usepath(char **cmd, char**env, t_mshell *ms, int i)
{
	struct stat		buf;
	char			*tmp;

	while (cmd[0] && ms->path && ms->path[i])
	{
		tmp = ft_strjoin(ft_strjoin(ms->path[i], "/"), cmd[0]);
		if (lstat(tmp, &buf) == 0)
		{
			if (fork() == 0)
			{
				if (execve(tmp, cmd, env) < 0
					&& ft_printf("%s not an executable\n", cmd[0]))
					exit(EXIT_SUCCESS);
			}
			/*if(flag && !close(ms->pfd[1]))
				close(ms->pfd[0]);*/
			wait(&ms->status);
		}
		free(tmp);
		i++;
	}
}

void	ft_exec_cmd2(char **cmd, char**env, t_mshell *ms)
{
	int	fd;

	fd = open(cmd[0], 0);
	if (fd > 0 && !close(fd))
	{
		if (ms->st_out != STDOUT)
		{
			if (execve(cmd[0], cmd, env) < 0
				&& ft_printf("%s not an executable\n", cmd[0]))
				exit(EXIT_SUCCESS);
		}
		else if (fork() == 0 && execve(cmd[0], cmd, env) < 0
			&& ft_printf("%s not an executable\n", cmd[0]))
			exit(EXIT_SUCCESS);
		wait(&ms->status);
		ms->status = WEXITSTATUS(ms->status);
	}
	else
		ft_usepath(cmd, env, ms, 0);
}
