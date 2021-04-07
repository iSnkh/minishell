/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:08:19 by wperu             #+#    #+#             */
/*   Updated: 2021/04/07 17:17:08 by wperu            ###   ########lyon.fr   */
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

void ft_usepath(char **cmd, char**env,t_mshell *ms ,int i)
{
	struct stat		buf;
	char			*tmp;

	
	while(cmd[0] && ms->path && ms->path[i])
	{
		
		tmp = ft_strjoin(ft_strjoin(ms->path[i],"/"),cmd[0]);
		printf("tmp = %s\n",tmp);
		if(stat(tmp, &buf) == 0)
		{
			puts("ok");
			if (fork() == 0)
			{
				puts("ok");
				if(execve(tmp,cmd + 1 ,env) < 0 
				&& ft_printf("%s not an executable\n",cmd[0]))
				exit(EXIT_SUCCESS);
			}
			ft_mgsignal(1);
			/*if(flag && !close(ms->pfd[1]))
				close(ms->pfd[0]);*/
			wait(&ms->status);
		}
		free(tmp);
		i++;
	}
}




void ft_exec_cmd2(char **cmd, char**env, t_mshell *ms)
{
    int	fd;

	if(!ft_strncmp(cmd[0], "./",2) || !ft_strncmp(cmd[0],"../",3)
		|| !ft_strncmp(cmd[0], "/",1))
	{
		if((fd = open(cmd[0],0)) > 0 && !close(fd))
		{
			if(ms->st_out != STDOUT)
			{
				if(execve(cmd[0], cmd + 1, env) < 0 
					&& ft_printf("%s not an executable\n",cmd[0])) // checker sans le if
					exit(EXIT_SUCCESS);
			}
			else if (fork() == 0 && execve(cmd[0],cmd + 1, env) < 0
				&& ft_printf("%s not an executable\n",cmd[0]))
				exit(EXIT_SUCCESS);
			ft_mgsignal(2); // a checker
			wait(&ms->status);
			ms->status = WEXITSTATUS(ms->status);
		}
	}
	else 
		ft_usepath(cmd,env,ms,0);
}

