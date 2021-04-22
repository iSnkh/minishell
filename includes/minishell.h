/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:57:12 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/21 05:41:06 by amonteli         ###   ########lyon.fr   */
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

# define LEXER_SPEC	" \t|;<>'\"\\"

#define TRUE 1
#define FALSE 0

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
		int				line_len;
		char			*pos;
		char			**env;
		struct s_token	*tokens;
		int				lex_status;
}						t_ms;

/**
 * 	
 */
typedef enum		e_token_type
{
	T_CMD = (1 << 0),
	T_RED = (1 << 1),
	T_PIPE = (1 << 2),
	T_SQUOTE = (1 << 3),
	T_DQUOTE = (1 << 4),
	T_PARAM = (1 << 5),
	T_SIMPLE = (1 << 6),
	T_SEP = (1 << 7)
}					t_token_type;

typedef enum		e_op_type
{
	OP_LREDIR = (1 << 0),
	OP_RREDIR = (1 << 1),
	OP_DREDIR = (1 << 2),
	OP_PIPE = (1 << 3),
}					t_op_type;

/**
 * FALLOC = Failed to allocate
 * FSYNTAX = Syntax error
 * FNOMATCH = Syntax not matching this lexer func
 * OK = OK 
 * END = End of the lexer.
 */

typedef enum		e_lexer_status
{
	LEXER_FALLOC = -3,
	LEXER_FSYNTAX = -2,
	LEXER_FNOMATCH = -1,
	LEXER_OK = 0,
	LEXER_END = 1,
}					t_lexer_status;

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

/**
 * 	lexer/tokenizer.c
 */

t_token		*ndup_token(const char *input, size_t n, int type);
void		token_add_front(t_token **tokens, t_token *token);
void		token_add_back(t_token **tokens, t_token *token);
int			create_cmd(t_token **tokens, t_token *line, t_token *data);
t_token		*new_token(void *data, int type);
void		clear_tokens(t_token **tokens);

/**
 *	lexer/space_lexer.c
 */

int					is_spaces(char c);
t_lexer_status		lex_spaces(void);

/**
 * lexer/param_lexer.c
 */

t_lexer_status	lex_param_simple(t_token **tokens, int flags);
t_lexer_status	lex_param(t_token **tokens, int flags);

/**
 * lexer/quotes_lexer.c
 */

t_lexer_status	lex_simple_quote(t_token **tokens, int flags);
t_lexer_status	lex_backslash(t_token **tokens, int flags, char **start);
t_lexer_status	lex_double_quote(t_token **tokens, int flags);
t_lexer_status	lex_quotes(t_token **tokens, int flags);

/**
 * lexer/redirection
 */

t_lexer_status	lex_redirection(t_token **tokens);

/**
 * lexer/command
 */

t_lexer_status	lex_cmd_simple(t_token **tokens);

/**
 * lexer/operator
 */

t_lexer_status	lex_operation(t_token **tokens);

t_lexer_status	lex_token(t_token **tokens);
t_lexer_status	lex_separator(t_token **tokens);
t_lexer_status	lex_tokens(t_token **tokens);

#endif
