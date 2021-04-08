/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:16:06 by wperu             #+#    #+#             */
/*   Updated: 2021/04/08 17:22:03 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_signal_c(int sign)
{
	sign = 0;
	write(1,"\nminishell> ",12);
}

void ft_signal_slash(int i)
{
    ft_printf("Quit: 3\n");
    signal(i, SIG_IGN);
}
void ft_nl(int i)
{
	ft_printf("\n");
	signal(i,SIG_IGN);
}
void ft_silence(int i)
{
    signal(i, SIG_IGN);
}

void    ft_mgsignal(int key)
{
	if(key == 0)
	{
		signal(SIGINT, &ft_signal_c);
		signal(SIGQUIT, &ft_silence);
	}
	else if(key == 1)
	{
		signal(SIGINT, &ft_nl);
		signal(SIGQUIT, &ft_signal_slash);
	}
	else
	{
		signal(SIGINT, &ft_silence);
		signal(SIGQUIT, &ft_silence);
	}
}