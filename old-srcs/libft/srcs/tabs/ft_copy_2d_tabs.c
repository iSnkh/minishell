/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_2d_tabs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 21:23:17 by amonteli          #+#    #+#             */
/*   Updated: 2020/10/13 22:24:38 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_copy_2d_tabs(char **tab)
{
	char	**dst;
	int		count;

	count = 0;
	while (tab[count])
		count++;
	if (!(dst = malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	count = -1;
	while (tab[++count])
		dst[count] = ft_strdup(tab[count]);
	dst[count] = 0;
	return (dst);
}
