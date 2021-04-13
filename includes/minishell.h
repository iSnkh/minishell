/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:02 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/13 17:29:02 by wperu            ###   ########lyon.fr   */
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
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/includes/libft.h"


# define CMD_SEPS "|;"
# define DQUOTE_EFFECT "\"\\"
# define	STDIN 0
# define	STDOUT 1
# define	STDERR 2

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

typedef struct s_redir
{
	int				fd;
	struct s_redir	*next;
}							t_redir;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}							t_env;

typedef struct s_mshell
{
	t_env	*env;
	int		pfd[2];
	int		p;
	char	**path;
	int		status;
	int		st_in;
	int		st_out;
	int		st_err;
	int		ret;
	int		ext;
	struct s_list	*cmds;
	struct s_list	*tokens;
}							t_mshell;

typedef t_mshell g_mshell;

int		main(int argc, char **argv, char **env);

int		minishell(char **envp);
void	ft_exec_cmd(char **cmd, char **env, t_mshell *ms);
void	free_array(char **array);
void	free_lst(void);
void	ft_dup_env(char **envp);
void	ft_add_env_var(char *var);
char	*ft_get_env_var(char *var);
char	**ft_lst_to_array(void);
bool	get_abs_path(char **cmd, char **envp);
void	ft_excute(t_mshell *ms, char **cmd);

// built-in

void	ft_replace_env(char *var, char *name); // en test
void	ft_joinvar(char *var, t_env *tmp);
void	ft_print_export(char *var, t_mshell *ms);
void	built_in_export(char **cmd, t_mshell *ms);
void	built_in_unset(char **cmd);
void	built_in_cd(char *path);
void	ft_change_path(char *oldpwd, char *pwd, char *pwd_ptr);
void	built_in_exit(char **cmd, t_mshell *msh);
char	*built_in_pwd(char *cmd);
void	built_in_env(t_mshell *ms);
int		exec_built_in(char **built_in, t_mshell *ms);
bool	is_built_in(char *cmd);
void	built_in_echo(char **cmd, t_mshell *ms);
void	ft_display_export(t_mshell *ms);
void	ft_add_env_export(char *var);
void	ft_manage_add_env(char *var, t_env *tmp);
int		ft_env_size(t_env *env);
int		ft_chr(char *str, char c);
int		ft_check_env(char *var, t_env *tmp);
char	*ft_trim(char *str, char c);
char	*ft_trimcpy(char *dst, char *str, char c);
int		ft_check_correct_var(char *var);

//libft
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strncat(char *dest, const char *src, size_t n);

//redir

void	ft_init_mshell(t_mshell *ms);
int		ft_parse_redir_v2(char **cmd, t_mshell *ms);
int		ft_redir(char **cmd, t_mshell *ms);
void	ft_clear_app(t_mshell *ms);
void	ft_pipe(t_mshell *ms, char **cmd);
void	shell_loop(void);

//signal

void	ft_signal_c(int sign);
void	ft_signal_slash(int i);
void	ft_silence(int i);
void	ft_nl(int i);
void	ft_manage_signal(int key);
void	ft_exec_cmd2(char **cmd, char**env, t_mshell *ms);
void	ft_usepath(char **cmd, char**env, t_mshell *ms, int i);
void	ft_gnl_minishell(t_mshell *ms, char **cmd, char *buffer);

//parsing

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


// TODO: DEBUG RM THAT
void	*print_commands(void *content);
void	*print_tokens(void *content);

#endif
