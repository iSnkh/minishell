/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:11:20 by wperu             #+#    #+#             */
/*   Updated: 2021/01/30 15:52:47 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_display_export()
{
    t_env	*tmp;

	tmp = first;
	while (tmp)
	{
		write(1,"declare -x ",11);
        ft_printf("%s\n", tmp->var_exprt);
		tmp = tmp->next;
	}
}


int ft_chr(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return(1);
        i++;
    }
    return(0);
}


void ft_add_env_export(char *var, int id)
{
    t_env   *tmp;
    t_env   *last;

    tmp = first;
    last = NULL;
    if(!(last = malloc(sizeof(t_env))))
        return ;
    last->var_exprt = ft_strdup(var);
    if(id == 1)
        last->var = NULL;
    else if(id == 2)
        last->var = ft_strdup(var);
    last->next = NULL;
    while(tmp->next)
        tmp= tmp->next;
    tmp->next = last;
}