/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:34:08 by wperu             #+#    #+#             */
/*   Updated: 2021/04/01 17:22:11 by wperu            ###   ########lyon.fr   */
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
	if (path == NULL)
		return ;
	else if (chdir(path) == 0)
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
	else
	{
		ft_putstr_fd("minishell: cd: ",STDERR);
		ft_putstr_fd(strerror(errno),STDERR);
		ft_putstr_fd("\n",STDERR);
	}
}

char	*built_in_pwd(char *cmd)
{
	char	*cwd;

	cwd = NULL;
	cwd = (char *)ft_calloc(sizeof(char), PATH_MAX + ft_strlen("PWD=") + 1);
	if (!cwd)
		return (NULL);
	strcat(cwd, "PWD=");
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

void	built_in_export(char **cmd, t_mshell *ms)
{
	if (cmd[1] == NULL || ms->st_out != STDOUT)
		ft_display_export(ms);
	else if (ft_check_correct_var(ft_trim(cmd[1], 34)) == 0)
	{
		ft_putstr_fd("minishell: export: `", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_fd("': not a valid identifier\n", STDERR);
	}
	else if (cmd[1] && cmd[1][0] != '=')
		ft_add_env_export(ft_trim(cmd[1], 34));
}	
	/*else if (cmd[1][0] == '=')
	{
		ft_putstr_fd("minishell: export: `",STDIN);
        ft_putstr_fd(cmd[1],STDIN);
        ft_putstr_fd("': not a valid identifier\n",STDIN);
	}*/
