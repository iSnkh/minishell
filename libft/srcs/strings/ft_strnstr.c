/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:44:30 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/16 03:39:51 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *need, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (need[0] == '\0')
		return ((char *)s);
	while (s[i] && i < len)
	{
		while (s[i + j] == need[j] && need[j] && i + j < len)
			j++;
		if (need[j] == '\0')
			return ((char *)&s[i]);
		i++;
		j = 0;
	}
	return (0);
}
