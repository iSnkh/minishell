/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.le-101.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 11:44:12 by amonteli          #+#    #+#             */
/*   Updated: 2020/02/17 09:33:42 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		pf_addspaces(t_pfinfo *p, int width)
{
	if (width < 0)
		width *= -1;
	pf_stradd(p, ft_memset(ft_calloc(width + 1, sizeof(char)), ' ', width));
}

void		pf_addzeros(t_pfinfo *p, int width)
{
	if (width < 0)
		width *= -1;
	pf_stradd(p, ft_memset(ft_calloc(width + 1, sizeof(char)), '0', width));
}
