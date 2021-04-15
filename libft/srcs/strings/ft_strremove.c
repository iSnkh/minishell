/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strremove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:10:59 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/08 18:11:13 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strremove(char *src, char c)
{
	int		count;
	int		occurence;
	char	*str;

	count = 0;
	occurence = 0;
	while (src[count])
	{
		if (src[count] == c)
			occurence++;
		count++;
	}
	str = malloc(sizeof(char) * (ft_strlen(src) - occurence + 1));
	count = 0;
	occurence = 0;
	while (src[count])
	{
		str[occurence] = src[count];
		if (src[count] != c)
			occurence++;
		count++;
	}
	str[occurence] = '\0';
	return (str);
}
