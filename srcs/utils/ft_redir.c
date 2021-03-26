/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:39:57 by wperu             #+#    #+#             */
/*   Updated: 2021/03/26 13:36:01 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_init_mshell(t_mshell *ms)
{
    ms->st_in = STDIN;
    ms->st_out = STDOUT;
    ms->st_err = STDERR;
    ms->ret = 0;
    ms->p = 0;
    ms->ext = 0;
}

void ft_parse_redir_v2(char **cmd, t_mshell *ms)
{
    int i;
    
    i = 0;
    while(cmd[i])
    {
        if(strcmp(cmd[i],">\0") == 0)
        	ms->st_out = open(cmd[i + 1], O_CREAT | O_WRONLY | O_TRUNC,  S_IRWXU); 
        else if(strcmp(cmd[i],">>\0") == 0)
            ms->st_out = open(cmd[i + 1], O_CREAT | O_WRONLY | O_APPEND,  S_IRWXU);
        else if (ft_strcmp(cmd[i],"|"))
			ms->p = 1;
		i++;
    }
}

void    ft_clear_app(t_mshell *ms)
{
    ft_init_mshell(ms);
}