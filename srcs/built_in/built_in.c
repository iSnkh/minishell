/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:34:08 by wperu             #+#    #+#             */
/*   Updated: 2021/04/09 15:49:15 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_cd(char *path)
{
	char	*oldpwd;
	char	*pwd;
	char	*pwd_ptr;

	oldpwd = NULL;
	pwd = NULL;
	pwd_ptr = NULL;
	if (path == NULL || ft_strcmp(path, "~") == 0)
	{
		if (chdir(ft_get_env_var("HOME=") + 5) == 0)
			ft_change_path(oldpwd, pwd, pwd_ptr);
	}
	else if (chdir(path) == 0)
		ft_change_path(oldpwd, pwd, pwd_ptr);
	else
	{
		ft_putstr_fd("minishell: cd: ", STDERR);
		ft_putstr_fd(path, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);
		ft_putstr_fd("\n", STDERR);
	}
}

void	ft_change_path(char *oldpwd, char *pwd, char *pwd_ptr)
{
	pwd = ft_strchr(ft_get_env_var("PWD="), '=') + 1;
	oldpwd = ft_strchr(ft_get_env_var("OLDPWD="), '=') + 1;
	if (oldpwd != NULL && pwd != NULL)
		oldpwd = ft_strjoin("OLDPWD=", ft_strdup(pwd));
	if (pwd != NULL)
	{
		pwd = &pwd[-ft_strlen("PWD=")];
		pwd_ptr = built_in_pwd("");
		pwd = ft_strdup(pwd_ptr);
		free(pwd_ptr);
		pwd_ptr = NULL;
	}
	ft_replace_env(pwd, "PWD=");
	ft_replace_env(oldpwd, "OLDPWD=");
}

char	*built_in_pwd(char *cmd)
{
	char	*cwd;

	cwd = NULL;
	cwd = (char *)ft_calloc(sizeof(char), PATH_MAX + ft_strlen("PWD=") + 1);
	if (!cwd)
		return (NULL);
	ft_strncat(cwd, "PWD=", 4);
	if (getcwd(&cwd[4], PATH_MAX) == NULL)
		perror("getcwd()");
	if (ft_strcmp(cmd, "pwd") == 0)
		return (cwd + 4);
	else
		return (cwd);
}

void	built_in_env(t_mshell *ms)
{
	t_env	*tmp;

	tmp = first;
	while (tmp)
	{
		if (ft_chr(tmp->var, '=') != (int)ft_strlen(tmp->var))
		{
			ft_putstr_fd(tmp->var, ms->st_out);
			ft_putstr_fd("\n", ms->st_out);
		}
		tmp = tmp->next;
	}
}

void	built_in_echo(char **cmd, t_mshell *ms)
{
	if (!(strcmp(cmd[1], "-n")))
		ft_putstr_fd(cmd[2], ms->st_out);
	else if ((strcmp(cmd[1], "-n")))
	{
		ft_putstr_fd(cmd[1], ms->st_out);
		ft_putstr_fd("\n", ms->st_out);
	}
}
