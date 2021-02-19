/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:12:14 by wperu             #+#    #+#             */
/*   Updated: 2021/02/19 10:03:31 by wperu            ###   ########lyon.fr   */
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

int exec_built_in(char **built_in, t_mshell *msh)
{
    if (!strcmp(built_in[0], "pwd"))
        ft_printf("%s\n",ft_get_env_var("PWD="));
    else if (!strcmp(built_in[0], "cd"))
        built_in_cd(built_in[1]);
    else if (!strcmp(built_in[0], "env"))
        built_in_env();
    else if (!strcmp(built_in[0], "echo"))
        built_in_echo(built_in);
    else if (!strcmp(built_in[0], "export"))
        built_in_export(built_in);
    else if (!strcmp(built_in[0], "unset"))
        built_in_unset(built_in);
    else if (!strcmp(built_in[0], "exit"))
    {
        built_in_exit(built_in, msh);
        return (1);
    }
    return(0);
}



int main(int argc, char **argv, char **envp)
{
    first = NULL;
    char *buffer = NULL;
    size_t buf_size = 2048;
    char **cmd = NULL;
    char **env = NULL;
    t_mshell msh;

    msh.ret = 0;
    msh.ext = 0;
    ft_dup_env(envp);
    (void)argc;
    (void)argv;
    if (!(buffer = (char *)ft_calloc(sizeof(char), buf_size)))
    {
        strerror(errno);
        return (EXIT_FAILURE);
    }
    write(1,"minishell> ",11);
    while (get_next_line(0, &buffer) > 0 && msh.ext != 1)
    {
        cmd = ft_split(buffer, ' ');
        if (cmd[0] == NULL)
            ft_printf("");
        else if (is_built_in(cmd[0]) == true)
            msh.ext = exec_built_in(cmd, &msh);
        else
        {
            env = ft_lst_to_array();
            if(get_abs_path(cmd,env) == true)
                ft_exec_cmd(cmd,env);
            else
                ft_printf("Commande not found\n");
            free(env);
            env = NULL;
        }
        if(msh.ext == 0)
            write(1,"minishell> ",11);
        free_array(cmd);
        if(msh.ext == 1)
            break;
    }
    free_lst();
    printf("Bye \n");
    free(buffer);
    return(msh.ret);
}