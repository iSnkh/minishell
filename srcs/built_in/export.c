/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 14:34:54 by wperu             #+#    #+#             */
/*   Updated: 2021/04/14 15:39:41 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_export(struct s_list *args, t_mshell *ms)
{
	
	if (args->content == NULL || ms->st_out != STDOUT)
		ft_display_export(ms);
	else
	{
		while(args->content)
		{
			if (ft_check_correct_var(ft_trim(args->content, 34)) == 0)
			{
				ft_putstr_fd("minishell: export: `", STDERR);
				ft_putstr_fd(args->content, STDERR);
				ft_putstr_fd("': not a valid identifier\n", STDERR);
			}
			else if (args->content)//&& (cmd->args->content[0] != '='))
				ft_add_env_export(ft_trim(args->content, 34));
		}
		args = args->next;
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

	tmp = ms->env;
	while (tmp)
	{
		write(ms->st_in, "declare -x ", 11);
		ft_print_export(tmp->var, ms);
		tmp = tmp->next;
	}
}
