/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:34:08 by wperu             #+#    #+#             */
/*   Updated: 2021/02/09 16:35:26 by wperu            ###   ########lyon.fr   */
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
	if (chdir(path) == 0)
	{
		pwd = ft_strrchr(ft_get_env_var("PWD="), '=') + 1;
		oldpwd = ft_strrchr(ft_get_env_var("OLDPWD="), '=') + 1;
		if (oldpwd != NULL && pwd != NULL)
			strcpy(oldpwd, pwd);
		if (pwd != NULL)
		{
			pwd = &pwd[-ft_strlen("PWD=")];
			pwd_ptr = built_in_pwd();
			strcpy(pwd, pwd_ptr);
			free(pwd_ptr);
			pwd_ptr = NULL;
		}
	}
	else
		perror("chdir");
}

char	*built_in_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	if (!(cwd = (char *)ft_calloc(sizeof(char), PATH_MAX
	+ ft_strlen("PWD=") + 1)))
		return (NULL);
	strcat(cwd, "PWD=");
	if (getcwd(&cwd[4], PATH_MAX) == NULL)
		perror("getcwd()");
	return (cwd);
}

void	built_in_env(void)
{
	t_env	*tmp;

	tmp = first;
	while (tmp)
	{
		if(ft_chr(tmp->var,'='))
			ft_printf("%s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	built_in_echo(char **cmd)
{
	if (!(strcmp(cmd[1], "-n")))
		ft_printf("%s", cmd[2]);
	else if ((strcmp(cmd[1], "-n")))
		ft_printf("%s\n", cmd[1]);
}

void	built_in_export(char **cmd)
{
	if (cmd[1] == NULL)
		ft_display_export();
	else if(ft_check_correct_var(ft_trim(cmd[1],34)) == 0)
		return ;
	else if (cmd[1] && cmd[1][0] != '=')
		ft_add_env_export(ft_trim(cmd[1],34));
	else if (cmd[1][0] == '=')
		ft_printf("minishell: export: `%s': not a valid identifier\n",cmd[1]);
	
}