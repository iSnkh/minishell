/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 12:16:31 by wperu             #+#    #+#             */
/*   Updated: 2021/03/22 15:46:14 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_pipe(t_mshell *ms, char **cmd)
{
    pid_t pid;
    pipe(ms->pfd);
    if((pid = fork()) == 0)
    {
        dup2(ms->pfd[1],1);
        ft_excute(ms, cmd);
        exit(0);
    }
    dup2(ms->pfd[0],0);
    close(ms->pfd[0]);
    close(ms->pfd[1]);
    while(wait(NULL)> 0)
        ;
}