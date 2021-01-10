/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 08:34:50 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/17 00:23:39 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char			*ft_utoa(unsigned int n)
{
	int		size;
	char	*tab;

	size = ft_numlen(n);
	if (!(tab = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	tab[size] = '\0';
	while (size)
	{
		tab[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
	return (tab);
}
