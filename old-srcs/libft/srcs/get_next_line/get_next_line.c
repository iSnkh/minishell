/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:36:36 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/16 03:06:55 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free(char *s1, char *s2, int action)
{
	int		count;
	int		s1_size;
	char	*tab;

	count = -1;
	s1_size = ft_strlen(s1);
	if (!(tab = (char *)malloc((s1_size + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	if (s1)
		while (s1[++count])
			tab[count] = s1[count];
	count = -1;
	if (s2)
		while (s2[++count])
			tab[s1_size + count] = s2[count];
	tab[s1_size + count] = '\0';
	if (action && s1)
		free(s1);
	return (tab);
}

int		ft_cut_buffer(char **line, t_gnl *current, t_gnl **first)
{
	int		size;
	char	*temp;
	t_gnl	*linked;

	linked = *first;
	if (!ft_strchr(current->content, '\n'))
	{
		*line = ft_strdup(current->content);
		if (linked != current)
		{
			while (linked->next && linked->next->fd != current->fd)
				linked = linked->next;
			linked->next = current->next;
		}
		free(current->content);
		free(current);
		linked == current ? *first = NULL : NULL;
		return (0);
	}
	size = (int)(ft_strchr(current->content, '\n') - current->content);
	*line = ft_substr(current->content, 0, size);
	temp = ft_strdup(current->content + size + 1);
	free(current->content);
	current->content = temp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_gnl	*lst;
	t_gnl			*current;
	char			buffer[BUFFER_SIZE + 1];
	int				readed;

	readed = 0;
	if (!line || BUFFER_SIZE < 1 || read(fd, buffer, 0) < 0)
		return (-1);
	if (!lst && !(lst = ft_create_list(fd)))
		return (-1);
	if (!(current = ft_lstchr(lst, fd)) &&
		!(current = ft_lstadd(&lst, ft_create_list(fd))))
		return (-1);
	while (!ft_strchr(current->content, '\n')
		&& (readed = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[readed] = '\0';
		current->content = ft_strjoin_free(current->content, buffer, 1);
	}
	return (ft_cut_buffer(line, current, &lst));
}
