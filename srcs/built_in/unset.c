/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 13:36:00 by wperu             #+#    #+#             */
/*   Updated: 2021/01/31 14:45:25 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void built_in_unset(char *cmd)
{
    t_env *tmp;
    t_env *after;

    tmp =first;
    while(tmp)
    {    
        if(ft_strncmp(tmp->next->var,cmd,ft_strlen(cmd) == 0))
            break;
        tmp = tmp->next;
    }
    if(tmp)
    {
        tmp = tmp->next->next
        
    }
    
}

void built_in_exit