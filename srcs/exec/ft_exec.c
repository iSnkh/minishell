/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 17:08:19 by wperu             #+#    #+#             */
/*   Updated: 2021/04/14 17:18:14 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_usepath(t_cmd *cmd, char**env, t_mshell *ms, int i)
{
	struct stat		buf;
	char			*tmp;

	while (cmd->cmd_name && ms->path && ms->path[i])
	{
		tmp = ft_strjoin(ft_strjoin(ms->path[i], "/"), cmd->cmd_name);
		if (lstat(tmp, &buf) == 0)
		{
			if (fork() == 0)
			{
				if (execve(tmp, cmd->args->content, env) < 0
					&& ft_printf("%s not an executable\n", cmd->cmd_name))
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

void	ft_exec_cmd2(t_cmd *cmd, char**env, t_mshell *ms)
{
	int	fd;

	fd = open(cmd->cmd_name, 0);
	if (fd > 0 && !close(fd))
	{
		if (ms->st_out != STDOUT)
		{
			if (execve(cmd->cmd_name, cmd->args->content, env) < 0
				&& ft_printf("%s not an executable\n", cmd->cmd_name))
				exit(EXIT_SUCCESS);
		}
		else if (fork() == 0 && execve(cmd->cmd_name, cmd->args->content, env) < 0
			&& ft_printf("%s not an executable\n", cmd->cmd_name))
			exit(EXIT_SUCCESS);
		ft_manage_signal(2);
		wait(&ms->status);
		ms->status = WEXITSTATUS(ms->status);
	}
	else
		ft_usepath(cmd, env, ms, 0);
}

void	ft_excute(t_mshell *ms, t_cmd *cmd)
{
	char	**env;

	env = NULL;
	if (cmd->cmd_name == NULL)
		return ;
	else if (is_built_in(cmd->cmd_name) == true)
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