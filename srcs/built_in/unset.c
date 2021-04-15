/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 13:36:00 by wperu             #+#    #+#             */
/*   Updated: 2021/04/14 17:06:49 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	built_in_unset(struct s_list *args)
{
	t_env	*tmp;
	t_env	*previous;
	t_env	*to_remove;
	struct s_list *tmparg;

	tmparg = args;
	while (tmparg->content)
	{	
		tmp = ms->env;
		previous = NULL;
		to_remove = NULL;
		while (tmp)
		{
			if (ft_strncmp(tmparg->content, tmp->var, ft_strlen(tmparg->content)) == 0)
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
		tmparg = tmparg->next;
	}
}
