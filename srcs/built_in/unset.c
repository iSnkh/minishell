/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 13:36:00 by wperu             #+#    #+#             */
/*   Updated: 2021/04/05 14:35:21 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_unset(char **cmd)
{
	t_env	*tmp;
	t_env	*previous;
	t_env	*to_remove;
	int		len;

	tmp = first;
	previous = NULL;
	to_remove = NULL;
	len = ft_chr(cmd[1], '=');
	while (tmp)
	{
		if (ft_strncmp(cmd[1], tmp->var, len) == 0)
		{
			to_remove = tmp;
			previous->next = tmp->next;
			free(to_remove);
			to_remove = NULL;
			break ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
}
