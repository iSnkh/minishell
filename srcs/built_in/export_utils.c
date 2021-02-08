/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:11:20 by wperu             #+#    #+#             */
/*   Updated: 2021/02/08 16:34:51 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *ft_trim(char *str, char c)
{
	int i;
	int j;
	int cpt;
	char *dst;

	i = 0;
	cpt = 0;
	dst = NULL;
	while(str[i])
	{
		if(str[i] == c)
			cpt++;
		i++;
	}
	if(!(dst = (char*)malloc(sizeof(char) * i-cpt + 1)))
		return(NULL);
	i = 0;
	j = 0;
	while(str[i])
	{
		if(str[i] == c)
			i++;
		else
		{
			dst[j] = str[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
	return(dst);
}



void ft_print_export(char *var)
{
	int i;
	int k;

    i = 0;
	k = 0;
    while(var[i])
    {
		 write(1,&var[i],1); 
		if(var[i] == '=' && k == 0)
		{
            ft_printf("%c",34);
			k = 1;
		}
		if(var[i + 1] == '\0' && k == 1)
			ft_printf("%c",34);
		i++;
    }
    write(1,"\n",1);
}


void ft_display_export()
{
    t_env	*tmp;

	tmp = first;
	while (tmp)
	{
		write(1,"declare -x ",11);
        ft_print_export(tmp->var);
		tmp = tmp->next;
	}
}


int ft_chr(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return(i);
        i++;
    }
    return(i);
}

int	ft_check_env(char *var,t_env *tmp)
{
	int len;
    

    len = ft_chr(var,'=');
	while (tmp)
	{
		if(ft_strncmp(var,tmp->var,len) == 0)
				return(1);
		tmp = tmp->next;
	}
	return(0);
}

void ft_change_var(char *var,t_env *tmp)
{
	int len;
    

    len = ft_chr(var,'=');
	while (tmp)
	{
		if(ft_strncmp(var,tmp->var,len) == 0)
		{
			free(tmp->var);
			tmp->var = ft_strdup(var);
			break;
		}		
		tmp = tmp->next;
	}
}

void ft_add_env_export(char *var)
{
    t_env   *tmp;
    t_env   *last;

    tmp = first;
    last = NULL;
	if (ft_check_env(var, tmp))
		ft_change_var(var,tmp);
	else
	{
		tmp = first;
		if (!(last = malloc(sizeof(t_env))))
        	return ;
    	last->var = ft_strdup(var);
    	last->next = NULL;
   		while(tmp->next)
        	tmp= tmp->next;
    	tmp->next = last;
	}
}