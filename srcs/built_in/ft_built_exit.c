/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 08:31:19 by wperu             #+#    #+#             */
/*   Updated: 2021/02/19 09:58:12 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void built_in_exit(char **cmd,t_mshell *msh)
{
    ft_printf("exit\n");
    msh->ret = ft_atoi(cmd[1]);
}