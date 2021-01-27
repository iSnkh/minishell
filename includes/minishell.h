/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:44:30 by amonteli          #+#    #+#             */
/*   Updated: 2021/01/27 17:01:42 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

enum
{
	MS_QUOTES = (1 << 0),
	MS_DQUOTES = (1 << 1),
	MS_PIPE = (1 << 2)
};

typedef struct		s_ms
{
		char		**env;
}					t_ms;

typedef struct		s_parser
{
		int			flags;
}					t_parser;

int		main(int argc, char **args, char **env);
void    built_in_cd(char *path);
void    build_in_pwd(void);

void	shell_loop();
#endif
