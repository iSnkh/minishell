/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:14:13 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/16 03:39:51 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_get_size(int number)
{
	int		count;

	count = 0;
	if (number < 0)
		number = -number;
	while (number > 9)
	{
		number = number / 10;
		count++;
	}
	count++;
	return (count);
}

char			*ft_itoa(int n)
{
	int		size;
	int		neg;
	char	*tab;

	size = ft_get_size(n);
	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		n = -n;
		neg = 1;
	}
	if (!(tab = (char *)malloc(sizeof(char) * (size + 1 + neg))))
		return (NULL);
	if (neg)
		tab[0] = '-';
	tab[size + neg] = '\0';
	while (size)
	{
		tab[size - (neg ? 0 : 1)] = n % 10 + '0';
		n = n / 10;
		size--;
	}
	return (tab);
}
