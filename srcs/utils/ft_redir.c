/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:39:57 by wperu             #+#    #+#             */
/*   Updated: 2021/03/22 16:17:21 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_init_mshell(t_mshell *ms)
{
    ms->st_in = STDIN;
    ms->st_out = STDOUT;
    ms->st_err = STDERR;
    ms->ret = 0;
    ms->p = 0;
    ms->ext = 0;
}

void ft_redir(t_mshell *ms,t_token *tokens)
{
    
    while(tokens)
    {
        
        if(tokens->rdir == 1)
            ms->st_in = open(tokens->tok, O_CREAT | O_WRONLY | O_TRUNC);
        else if(tokens->rdir == 2)
            ms->st_in = open(tokens->tok, O_CREAT | O_WRONLY | O_APPEND);
        if(tokens->next)
            close(ms->st_in);
        tokens = tokens->next;
    }
}

void ft_parse_redir(char **cmd,t_mshell *ms,t_token *tokens)
{
    int i;

    i = 0;
    while(cmd[i])
    {
        if(cmd[i][0] == '>' && cmd[i][1] == '\0')
        {    
            ft_add_token(cmd[i + 1], tokens, 1);
            puts("ok");
        }
        else if(strcmp(cmd[i],">>"))
            ft_add_token(cmd[i +1], tokens, 2);
        else if (cmd[i][0] == '|')
            ms->p = 1;
        i++;
        printf("tokens = %s ,rdir = %d\n",tokens->tok,tokens->rdir);
    }
}

t_token	*ft_add_token(char *var, t_token *tokens, int rdir)
{
	t_token *tmp;
    t_token *new;

	tmp = tokens;
    if(var == NULL)
		return(NULL);
	if(!( new = (t_token *)ft_calloc(sizeof(t_token), 1)))
		return(NULL);
	new->tok = var;
	new->rdir = rdir;
    new->next = NULL;
	if(tmp == NULL)
		tmp = new;
	else
	{
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next= new;
	}
    return(new);
}

void    ft_clear_app(t_token *tokens,t_mshell *ms)
{
    t_token *tmp = tokens;
    t_token *tmp2 = tmp;
    ft_init_mshell(ms);
    while(tmp)
    {
        tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2->tok);
        tmp2->tok = NULL;
        free(tmp2);
        tmp = NULL;
    }
}