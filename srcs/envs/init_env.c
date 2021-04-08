/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:36:27 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/08 14:43:42 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_env_var(char *var)
{
	t_env	*tmp;
	size_t	len;

	tmp = first;
	len = ft_strlen(var);
	while (tmp)
	{
		if (!ft_strncmp(var, tmp->var, len))
			return (tmp->var);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_add_env_var(char *var)
{
	t_env	*env1;
	t_env	*new;

	if (var == NULL)
		return ;
	env1 = first;
	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		return ;
	new->var = var;
	new->next = NULL;
	if (env1 == NULL)
		first = new;
	else
	{
		while (env1-> next != NULL)
			env1 = env1->next;
		env1->next = new;
	}
}

static void ft_affiche_path(char **path)
{
	int i = 0;
	while(path[i])
	{
		printf("%s\n",path[i]);
		i++;
	}
}

void	ft_dup_env(char **envp, t_mshell *ms)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		/*if(ft_strncmp(envp[i],"PATH=",5) == 0)
			ms->path = ft_split(envp[i] + 5, ':');*/
		ft_add_env_var(ft_strdup(envp[i]));
		i++;
	}
}

void	ft_replace_env(char *var, char *name)
{
	t_env	*tmp;

	tmp = first;
	while (tmp)
	{
		if (ft_strncmp(name, tmp->var, ft_strlen(name)) == 0)
		{
			free(tmp->var);
			tmp->var = ft_strdup(var);
		}
		tmp = tmp->next;
	}
}
