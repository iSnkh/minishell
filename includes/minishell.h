/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:31:02 by amonteli          #+#    #+#             */
/*   Updated: 2021/02/17 15:53:14 by wperu            ###   ########lyon.fr   */
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
# include "../libft/includes/libft.h"


typedef struct		s_env
{
		char				*var;
		struct s_env		*next;
}					t_env;

t_env *first;

int		main(int argc, char **argv, char **env);

void	ft_exec_cmd(char **cmd, char **env);
void	free_array(char **array);
void	free_lst(void);

void    ft_dup_env(char **envp);
void	ft_add_env_var(char *var);
char	*ft_get_env_var(char *var);
char	**ft_lst_to_array();
bool	get_abs_path(char **cmd, char **envp);


// built-in

void	ft_joinvar(char *var, t_env *tmp);
void 	ft_print_export(char *var);
void	built_in_export(char **cmd);
void 	built_in_unset(char **cmd);
void	built_in_cd(char *path);
char	*built_in_pwd(void);
void	built_in_env(void);
void 	exec_built_in(char **built_in);
bool	is_built_in(char *cmd);
void	built_in_echo(char **cmd);
void	ft_display_export();
void	ft_add_env_export(char *var);
int		ft_env_size(t_env *env);
int		ft_chr(char *str, char c);
int 	ft_check_env(char *var,t_env *tmp);
char 	*ft_trim(char *str, char c);
void 	ft_putstrn(char *var, int len);
int		ft_check_correct_var(char *var);

void	shell_loop();
#endif
