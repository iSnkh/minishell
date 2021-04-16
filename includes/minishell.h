/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:57:12 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/16 22:33:47 by amonteli         ###   ########lyon.fr   */
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

/**
 * 	struct s_ms
 * 		env: environement
 */

typedef struct			s_ms
{
		char			**env;
}						t_ms;

/**
 * struct s_cmd
 * 		cmd_name: (echo|ls|etc...)
 */

typedef struct				s_cmd
{
		char 				*cmd_name;
		struct s_list		*args;
		int					flags;
}							t_cmd;

t_ms	*ms;


/**
 * 	srcs/main.c
 * 		main(argc, args, env);
 */

int		main(int argc, char **args, char **env);


/**
 * 	utilities/ui.c
 * 		clear_console(void)
 */

void	clear_console(void);

#endif
