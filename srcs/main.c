/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:12:14 by wperu             #+#    #+#             */
/*   Updated: 2021/04/06 16:57:51 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>

bool is_built_in(char *cmd)
{
    const char  *built_in[]= {"cd", "pwd", "env", "echo", "export", "unset","exit", NULL};
    int         i;

    i = 0;

    while(built_in[i])
    {
        
        if(!strcmp(built_in[i], cmd))
            return (true);
        i++;
    }
    return (false);
}

int exec_built_in(char **built_in, t_mshell *ms)
{
    char *pwd;

    if (!strcmp(built_in[0], "pwd"))
    {
        pwd = built_in_pwd(built_in[0]);
        ft_putstr_fd(pwd,ms->st_out);
	    ft_putstr_fd("\n",ms->st_out);
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
    return(0);
}

void ft_excute(t_mshell *ms, char **cmd)
{
    char **env;

    env = NULL;
    if (cmd[0] == NULL)
            ft_printf("");
    else if (is_built_in(cmd[0]) == true)
        ms->ext = exec_built_in(cmd, ms);
    else
    {
        env = ft_lst_to_array();
        if(get_abs_path(cmd,env) == true)
            ft_exec_cmd(cmd,env,ms);
        else
        {    
            ft_printf("Commande not found\n");
            free(env);
            env = NULL;
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    first = NULL;
    char *buffer = NULL;
    size_t buf_size = 2048;
    char **cmd = NULL;
    t_mshell ms;

    
    ft_init_mshell(&ms);
    ft_dup_env(envp,&ms);
    (void)argc;
    (void)argv;
    if (!(buffer = (char *)ft_calloc(sizeof(char), buf_size)))
    {
        strerror(errno);
        return (EXIT_FAILURE);
    }
    signal(SIGINT,&ft_signal_c);
    signal(SIGQUIT,SIG_IGN);
    write(1,"minishell> ",11);
    while (get_next_line(0, &buffer) > 0 && ms.ext != 1)
    {
        
        cmd = ft_split(buffer, ' '); // parse
        int i = 0 ;
        while (cmd[i])
        {
            ft_printf("cmd[%d] = %s\n",i,cmd[i]);
            i++;
        }
        if (ft_parse_redir_v2(cmd, &ms) == 1)
            ft_excute(&ms, cmd);
        if (ms.ext == 0)
            write(1,"minishell> ",11);
        if (ms.ext == 1)
            break;
        free_array(cmd);
        ft_clear_app(&ms);
    }
    if(ms.ext != 1)
        ft_printf("exit\n");
    free_lst();
    printf("Bye \n");
    free(buffer);
    return(ms.ret);
}
/*
void ft_gnl_minishell(t_mshell *ms, char **cmd, char *buffer, int buf_size)
{
    char *buffer = NULL;
    size_t buf_size = 2048;

    buffer = NULL;
    buf_size = 2048;  
    while (get_next_line(0, &buffer) > 0 && ms.ext != 1)
    {
        if (!(buffer = (char *)ft_calloc(sizeof(char), buf_size)))
        {
            strerror(errno);
            return (EXIT_FAILURE);
        }
        cmd = ft_split(buffer, ' '); // parse
        int i = 0 ;
        while (cmd[i])
        {
            ft_printf("cmd[%d] = %s\n",i,cmd[i]);
            i++;
        }
        if (ft_parse_redir_v2(cmd, &ms) == 1)
            ft_excute(&ms, cmd);
        if (ms.ext == 0)
            write(1,"minishell> ",11);
        if (ms.ext == 1)
            break;
        free_array(cmd);
        ft_clear_app(&ms);
    }
}*/