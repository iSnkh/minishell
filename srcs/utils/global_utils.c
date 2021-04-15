/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 13:15:41 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/14 16:51:42 by wperu            ###   ########lyon.fr   */
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

void	free_lst(void)
{
	t_env	*index;
	t_env	*tmp;

	index = ms->env;
	tmp = index;
	while (index != NULL)
	{
		tmp = index;
		index = index->next;
		free(tmp->var);
		tmp->var = NULL;
		free(tmp);
		tmp = NULL;
	}
}

char	**ft_lst_to_array(void)
{
	char	**array;
	t_env	*tmp;
	int		i;

	array = NULL;
	tmp = ms->env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	array = (char **)ft_calloc(sizeof(char *), i + 1);
	if (!array)
		exit(-1);
	tmp = ms->env;
	i = 0;
	while (tmp)
	{
		array[i] = tmp->var;
		tmp = tmp->next;
		i++;
	}
	return (array);
}
