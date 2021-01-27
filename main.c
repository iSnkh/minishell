/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:12:14 by wperu             #+#    #+#             */
/*   Updated: 2021/01/27 15:27:35 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <errno.h>

bool is_built_in(char *cmd)
{
    const char  *built_in[]= {"cd", "pwd", "env","echo", NULL};
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

void exec_built_in(char **built_in)
{
    if (!strcmp(built_in[0], "pwd"))
        ft_printf("%s\n",ft_get_env_var("PWD="));
    else if (!strcmp(built_in[0], "cd"))
        built_in_cd(built_in[1]);
    else if (!strcmp(built_in[0], "env"))
        built_in_env();
    else if (!strcmp(built_in[0], "echo"))
        built_in_echo(built_in);
}



int main(int argc, char **argv, char **envp)
{
    first = NULL;
    exprt = NULL;
    char *buffer = NULL;
    size_t buf_size = 2048;
    char **cmd = NULL;
    char **env = NULL;

    ft_dup_env(envp);
    (void)argc;
    (void)argv;
    if (!(buffer = (char *)ft_calloc(sizeof(char), buf_size)))
    {
        strerror(errno);
        return (EXIT_FAILURE);
    }
    write(1,"minishell> ",11);
    while (get_next_line(0, &buffer) > 0)
    {
        cmd = ft_split(buffer, ' ');
        if (cmd[0] == NULL)
            ft_printf("Command not found\n");
        else if (is_built_in(cmd[0]) == true)
            exec_built_in(cmd);
        else
        {
            puts("OK");
            env = ft_lst_to_array();
            if(get_abs_path(cmd,env) == true)
                ft_exec_cmd(cmd,env);
            else
                ft_printf("Commande not found\n");
            free(env);
            env = NULL;
        }
        write(1,"minishell> ",11);
        free_array(cmd);
    }
    free_lst();
    printf("Bye \n");
    free(buffer);
    return(0);
}