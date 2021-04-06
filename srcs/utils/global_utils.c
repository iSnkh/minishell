/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:15:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/06 17:08:13 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
}

bool	get_abs_path(char **cmd, char **envp)
{
	char	*path;
	char	*bin;
	char	**path_split;
	size_t	index;
	int		i;

	path = NULL;
	bin = NULL;
	path_split = NULL;
	index = 0;
	i = 0;
	if (cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2) != 0)
	{
		while (envp[i])
		{
			if (!ft_strncmp(envp[i], "PATH=", 5))
			{
				path = ft_strdup(&envp[i][5]);
				break ;
			}
			i++;
		}
		if (path == NULL)
			return (false);
		path_split = ft_split(path, ':');
		free(path);
		path = NULL;
		while (path_split[index])
		{
			if (!(bin = (char *)ft_calloc(sizeof(char), (ft_strlen(path_split[index]) + 1 + ft_strlen(cmd[0]) + 1))))
				break;
			strcat(bin, path_split[index]);
			strcat(bin, "/");
			strcat(bin, cmd[0]);

			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
			index++;

		}
		free_array(path_split);
		free(cmd[0]);
		cmd[0] = bin;
	}
	else
	{
		free(path);
		path = NULL;
	}
	if (bin == NULL)
		return (false);
	else
		return (true);
}

void free_lst(void)
{
	t_env	*index;
	t_env	*tmp; 
	
	index = first;
	tmp = index;
	while (index != NULL)
	{
		tmp = index;
		index = index->next;
		free(tmp->var);
		tmp->var= NULL;
		free(tmp);
		tmp = NULL;
	}
}

char	**ft_lst_to_array()
{
	char	**array;
	t_env	*tmp;
	int		i;

	array = NULL;
	tmp = first;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!array)
		exit(-1);
	tmp = first;
	i = 0;
	while (tmp)
	{
		array[i] = tmp->var;
		tmp = tmp->next;
		i++;
	}
	return (array);
}
