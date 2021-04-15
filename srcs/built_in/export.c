/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:34:54 by wperu             #+#    #+#             */
/*   Updated: 2021/04/15 15:57:01 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_export(char **cmd, t_mshell *ms)
{
	int	i;

	if ((cmd[0 + 1] == NULL && ft_strcmp(cmd[0],"export") == 0) || ms->st_out != STDOUT)
			ft_display_export(ms);
	i = 1;
	while(cmd[i])
	{
		if (ft_check_correct_var(ft_trim(cmd[i], 34)) == 0)
		{
			ft_putstr_fd("minishell: export: `", STDERR);
			ft_putstr_fd(cmd[i], STDERR);
			ft_putstr_fd("': not a valid identifier\n", STDERR);
		}
		else if (cmd[i] && cmd[i][0] != '=')
			ft_add_env_export(ft_trim(cmd[i], 34));
		i++;
	}
}

void	ft_print_export(char *var, t_mshell *ms)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (var[i])
	{
		write(ms->st_in, &var[i], 1);
		if (var[i] == '=' && k == 0)
		{
			ft_putstr_fd("\"", ms->st_in);
			k = 1;
		}
		if (var[i + 1] == '\0' && k == 1)
			ft_putstr_fd("\"\n", ms->st_in);
		if (var[i + 1] == '\0' && k == 0)
			ft_putstr_fd("\n", ms->st_in);
		i++;
	}
}

void	ft_display_export(t_mshell *ms)
{
	t_env	*tmp;

	tmp = first;
	while (tmp)
	{
		write(ms->st_in, "declare -x ", 11);
		ft_print_export(tmp->var, ms);
		tmp = tmp->next;
	}
}
