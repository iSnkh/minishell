/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:57:12 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/17 15:55:56 by amonteli         ###   ########lyon.fr   */
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

#define TRUE 1
#define FALSE 2

#define UNCOMPLETED_DQUOTE -3
#define UNCOMPLETED_QUOTE -4
#define CHECKER_SLASH -2

/**
 * 	struct s_ms
 * 		env: environement
 */

typedef struct			s_ms
{
		int				count;
		char			*line;
		char			*line_len;
		char			*pos;
		char			**env;
		struct s_token	*tokens;
}						t_ms;

/**
 * 	
 */
typedef enum		e_token_type
{
	T_CMD = (1 << 0),
	T_RED = (1 << 1),
	T_PIPE = (1 << 2),
}					t_token_type;

typedef enum		e_op_type
{
	OP_LREDIR = (1 << 0),
	OP_RREDIR = (1 << 1),
	OP_DREDIR = (1 << 2),
	OP_PIPE = (1 << 3),
}					t_op_type;

/**
 * 	EALLOC = Failed to malloc
 * 	ESYNTAX = Syntax invalid
 * 	ENOMATCH = No matching this scheme
 * 	EOK = OK
 * 	EEND = End of the input
 */

typedef enum		e_lex_err
{
	LX_EALLOC = -3,
	LX_ESYNTAX = -2,
	LX_ENOMATCH = -1,
	LX_EOK = 0,
	LX_EEND = 1,
}					t_lex_err;

/**
 * struct s_cmd
 * 		cmd_name: (echo|ls|etc...)
 */

typedef struct				s_token
{
		int 				type;
		void				*data;
		struct s_token		*next;
}							t_token;

t_ms	*ms;


/**
 * 	srcs/main.c
 * 		main(argc, args, env);
 */

int		main(int argc, char **args, char **env);

/**
 * 	checker/input_checker.c
 * 		check input like backslash at EOF
 */

int		check_line_input(char *line);

/**
 * 	utilities/ui.c
 * 		clear_console(void);
 */

void	clear_console(void);

/**
 * 	splitter/separator.c
 * 		split_by_separator(char *line);
 */

int		split_by_separator(char *line);
int		fetch_command(char *line);

#endif
