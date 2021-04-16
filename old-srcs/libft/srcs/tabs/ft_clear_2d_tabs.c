/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_2d_tabs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 00:57:54 by amonteli          #+#    #+#             */
/*   Updated: 2020/10/11 00:59:50 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_clear_2d_tabs(void **tab)
{
	int		count;

	count = 0;
	while (tab[count])
		free(tab[count++]);
	free(tab);
}
