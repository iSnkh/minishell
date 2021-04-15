/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:12:14 by wperu             #+#    #+#             */
/*   Updated: 2021/04/15 16:54:56 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>

bool	is_built_in(char *cmd)
{
	char	**built_in;
	int		i;

	i = 0;
	built_in = ft_split("cd pwd env echo export unset exit", ' ');
	while (built_in[i])
	{
		if (!strcmp(built_in[i], cmd))
		{
			free(built_in);
			return (true);
		}
		i++;
	}
	free(built_in);
	return (false);
}

int	exec_built_in(char **built_in, t_mshell *ms)
{
	char	*pwd;

	if (!strcmp(built_in[0], "pwd"))
	{
		pwd = built_in_pwd(built_in[0]);
		ft_putstr_fd(pwd, ms->st_out);
		ft_putstr_fd("\n", ms->st_out);
	}
	else if (!strcmp(built_in[0], "cd"))
		built_in_cd(built_in[1]);
	else if (!strcmp(built_in[0], "env"))
		built_in_env(ms);
	else if (!strcmp(built_in[0], "echo"))
		built_in_echo(built_in, ms);
	else if (!strcmp(built_in[0], "export"))
		built_in_export(built_in, ms);
	else if (!strcmp(built_in[0], "unset"))
		built_in_unset(built_in);
	else if (!strcmp(built_in[0], "exit"))
	{
		built_in_exit(built_in, ms);
		return (1);
	}
	return (0);
}

int	minishell(char **envp)
{
	char		*buffer;
	size_t		buf_size;
	char		**cmd;
	t_mshell	ms;

	cmd = NULL;
	first = NULL;
	buffer = NULL;
	buf_size = 2048;
	ft_init_mshell(&ms);
	ft_dup_env(envp);
	buffer = (char *)ft_calloc(sizeof(char), buf_size);
	if (!buffer)
	{
		strerror(errno);
		return (EXIT_FAILURE);
	}
	signal(SIGINT, &ft_signal_c);
	signal(SIGQUIT, &ft_silence);
	write(1, "minishell> ", 11);
	ft_gnl_minishell(&ms, cmd, buffer);
	free_lst();
	ft_printf("Bye \n");
	free(buffer);
	return (ms.ret);
}

void	ft_gnl_minishell(t_mshell *ms, char **cmd, char *buffer)
{
	int	i;

	while (get_next_line(0, &buffer) > 0 && ms->ext != 1)
	{
		cmd = ft_split(buffer, ' ');// ft_parse();
		i = 0;
		if (ft_parse_redir_v2(cmd, ms) == 1)
			ft_excute(ms, cmd);
		if (ms->ext == 0)
			write(1, "minishell> ", 11);
		if (ms->ext == 1)
			break ;
		free_array(cmd);
		ft_clear_app(ms);
	}
	if (ms->ext != 1)
		ft_printf("exit\n");
	free(buffer);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc == 1)
		return (minishell(envp));
	else
		return (0);
}
