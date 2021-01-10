/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 17:16:51 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/16 03:39:51 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t			count;
	unsigned char	*source;
	unsigned char	*d;

	count = 0;
	source = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (!src && !dest)
		return (NULL);
	while (count < n)
	{
		d[count] = source[count];
		if (source[count] == (unsigned char)c)
			return (d + count + 1);
		count++;
	}
	return (0);
}
