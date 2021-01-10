/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 16:36:38 by amonteli          #+#    #+#             */
/*   Updated: 2020/07/16 03:23:51 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 64

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef	struct		s_gnl
{
	int				fd;
	char			*content;
	struct s_gnl	*next;
}					t_gnl;

int					get_next_line(int fd, char **line);
int					ft_cut_buffer(char **line, t_gnl *current, t_gnl **first);

/*
** get_next_line_utils.c
*/

char				*ft_strjoin_free(char *s1, char *s2, int action);
t_gnl				*ft_create_list(int fd);
t_gnl				*ft_lstchr(t_gnl *list, int fd);
t_gnl				*ft_lstadd(t_gnl **alst, t_gnl *new);

#endif
