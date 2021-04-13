/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:08:19 by wperu             #+#    #+#             */
/*   Updated: 2021/04/10 18:01:06 by wperu            ###   ########lyon.fr   */
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
			ft_manage_signal(1);
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
		ft_manage_signal(2);
		wait(&ms->status);
		ms->status = WEXITSTATUS(ms->status);
	}
	else
		ft_usepath(cmd, env, ms, 0);
}

void	ft_excute(t_mshell *ms, char **cmd)
{
	char	**env;

	env = NULL;
	if (cmd[0] == NULL)
		ft_printf("");
	else if (is_built_in(cmd[0]) == true)
		ms->ext = exec_built_in(cmd, ms);
	else
	{
		env = ft_lst_to_array();
		if (ft_get_env_var("PATH="))
		{
			ms->path = ft_split(ft_get_env_var("PATH=") + 5, ':');
			ft_exec_cmd2(cmd, env, ms);
		}
		else
			ft_printf("minishell: Command not found\n");
		free(env);
		env = NULL;
	}
}