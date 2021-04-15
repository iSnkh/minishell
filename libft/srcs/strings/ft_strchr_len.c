/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 05:25:25 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/23 16:59:58 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int		ft_strchr_len(const char *s, int c)
{
	int		count;

	count = -1;
	while (s[++count])
		if (s[count] == c)
			return (count);
	if (s[count] == c)
		return (count);
	return (-1);
}
