/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 11:44:30 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/25 19:05:02 by amonteli         ###   ########lyon.fr   */
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

#define CMD_SEPS "|><;"

enum					e_flags_token
{
	MS_QUOTES = (1 << 0),
	MS_DQUOTES = (1 << 1),
	MS_PIPE = (1 << 2),
	MS_SEP = (1 << 3),
	MS_SLASH = (1 << 4),
	MS_LREDIR = (1 << 5),
	MS_RREDIR = (1 << 6),
	MS_ENV = (1 << 7)
};

enum					e_flags_cmds
{
	CMD_LREDIR = (1 << 0),
	CMD_RREDIR = (1 << 1),
	CMD_PIPE = (1 << 2),
	CMD_PARSED = (1 << 3),
	CMD_DREDIR = (1 << 4),
	CMD_SEP = (1 << 5)
};

typedef struct			s_ms
{
		char			**env;
		struct s_list	*cmds;
		struct s_list	*tokens;
}						t_ms;

typedef struct				s_env
{
		char				*var;
		struct s_env		*next;
}							t_env;

typedef struct				s_cmd
{
		char 				*cmd_name;
		struct s_list		*args;
		int					flags;
}							t_cmd;

typedef struct				s_token
{
		char				*token;
		int					flags;
}							t_token;

t_ms	*ms;

int		main(int argc, char **args, char **env);
void    built_in_cd(char *path);
void    build_in_pwd(void);

void	shell_loop();

void	*print_tokens(void *content);


// global_utils.c
void	clear_console();
// t_cmd	*create_cmd(char *command);
t_token	*create_token(char *token, int flags);
int		is_escaped(t_token *token);
int		is_cmd_sep(char c);

// tokenizer.c
int		tokenize(char *line);

// parser.c
void		parse(char *line);

// tokenizer_utils.c
int		tokenize_quote(char *line);
int		tokenize_dquote(char *line);
int		has_to_tokenize(char *line);
int		get_len_to_token(char *line);

// env_manager
void	replace_env(t_list *list);

// commands/utils.c
t_cmd	*create_cmd(t_list *tokens);

// commands/spliter.c
void	split_into_commands();

// exec
void	exec(void);

//	commands/formater.c
void	format_commands(void);


#endif
