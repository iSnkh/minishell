/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 18:14:29 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/29 18:14:36 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *src, char *from, char *to)
{
	char	*str;
	int		len;
	int		pos;

	len = (ft_strlen(src) - ft_strlen(from)) + ft_strlen(to) + 1;
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	pos = (int)(ft_strnstr(src, from, ft_strlen(src)) - src);
	ft_strncpy(str, src, pos);
	ft_strcpy(str + pos, to);
	ft_strcpy(str + pos + ft_strlen(to), src + pos + ft_strlen(from));
	return (str);
}
