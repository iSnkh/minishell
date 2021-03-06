/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:44:30 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/06 16:19:50 by amonteli         ###   ########lyon.fr   */
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
	MS_PIPE = (1 << 2),
	MS_SEP = (1 << 3),
	MS_SLASH = (1 << 4),
	MS_LREDIR = (1 << 5),
	MS_RREDIR = (1 << 6),
};

typedef struct		s_ms
{
		char			**env;
		struct s_list	*cmds;
		struct s_list	*tokens;
}					t_ms;

typedef struct				s_env
{
		char				*var;
		struct s_env		*next;
}							t_env;

typedef struct		s_cmd
{
		char 			*cmd;
		struct s_parser	*parser;
}					t_cmd;

typedef struct		s_token
{
		char		*token;
		int			flags;
}					t_token;

t_ms	*ms;

int		main(int argc, char **args, char **env);
void    built_in_cd(char *path);
void    build_in_pwd(void);

void	shell_loop();

// global_utils.c
void	clear_console();
t_cmd	*create_cmd(char *command);
t_token	*create_token(char *token, int flags);

// tokenizer.c
int		tokenize(char *line);

// parser.c
void		parse(char *line);

// tokenizer_utils.c
int		tokenize_quote(char *line);
int		tokenize_dquote(char *line);
int		has_to_tokenize(char *line);
int		get_len_to_token(char *line);


#endif
