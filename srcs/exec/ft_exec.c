/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:08:19 by wperu             #+#    #+#             */
/*   Updated: 2021/04/06 18:43:52 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exec_cmd(char **cmd, char **env, t_mshell *ms)
{
	pid_t	pid;
	int		status;

    status = 0;
	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (ms->st_out != STDOUT)
		{
			dup2(ms->st_out, STDOUT);
			close(ms->st_out);
		}
		if (execve(cmd[0], cmd, env) == -1)
			perror("shell");
		exit(EXIT_FAILURE);
	}
}

void ft_exec_cmd(char **cmd, char**env, t_mshell *ms)
{
    int	fd;

	if(!ft_strncmp(com, "./",2) || !ft_strncmp("../",3))
		|| !ft_strncmp(com, "/",1))
	{
		if(fd = open(com,0)) > 0 && !close(fd))
		{
			if(flag)
			{
				if(execve(com[0], com + 1, env) < 0 
					&& ft_printf("%s not an executable\n",com))
					exit(EXIT_SUCCESS);
			}
			else if (fork() == 0 && execve(com[0],com + 1, env) < 0
				&& ft_printf("%s not an executable\n",com))
				exit(EXIT_SUCCESS);
			ft_input(2); // a checker
		}
	}
}