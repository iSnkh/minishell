/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:04:34 by wperu             #+#    #+#             */
/*   Updated: 2021/02/09 16:36:19 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_putstrn(char *var, int len)
{
    int i;

    i = 0;
    while(i < len)
        write(1,&var[i++],1);
}


int ft_check_correct_var(char *var)
{
    int len;
    int i;

    i = 0;
    if((len = ft_chr(var,'=')) != 0)
    {
        if(var[len - 1] == '+')
            len--;
    }
    while(i < len)
    {
        if((var[i]>='0' && var[i]<='9') || var[i] == '_' ||
            (var[i]>='a' && var[i]<='z') ||
            (var[i]>='A' && var[i]<='Z'))
            i++;
        else
        {
            ft_printf("minishell: export: `");
            ft_putstrn(var,len);
            ft_printf("': not a valid identifier\n");
            return(0);
        }   
    }
    return(1);
}