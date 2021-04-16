/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strbaselen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 23:05:28 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/17 00:26:25 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long		ft_strbaselen(unsigned long long n, char *base)
{
	long unsigned int	len;

	len = 1;
	while (n /= ft_strlen(base))
		len++;
	return (len);
}
