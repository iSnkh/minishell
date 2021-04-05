/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:04:34 by wperu             #+#    #+#             */
/*   Updated: 2021/04/05 14:23:55 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_correct_var(char *var)
{
	int	len;
	int	i;

	i = 0;
	len = ft_chr(var, '=');
	if (len != 0)
	{
		if (var[len - 1] == '+')
			len--;
	}
	while (i < len)
	{
		if ((var[i] >= '0' && var[i] <= '9') || var[i] == '_'
			|| (var[i] >= 'a' && var[i] <= 'z')
			|| (var[i] >= 'A' && var[i] <= 'Z'))
			i++;
		else
			return (0);
	}
	return (1);
}

char	*ft_trim(char *str, char c)
{
	int		i;
	int		cpt;
	char	*dst;

	i = 0;
	cpt = 0;
	dst = NULL;
	while (str[i])
	{
		if (str[i] == c)
			cpt++;
		i++;
	}
	dst = (char *)malloc(sizeof(char) * i - cpt + 1);
	if (!dst)
		return (NULL);
	return (ft_trimcpy(dst, str, c));
}

char	*ft_trimcpy(char *dst, char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			dst[j] = str[i];
			i++;
			j++;
		}
	}
	dst[j] = '\0';
	return (dst);
}

int	ft_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	ft_joinvar(char *var, t_env *tmp)
{
	int	i;

	i = ft_chr(var, '=');
	i--;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->var, i) == 0)
		{
			if (ft_chr(tmp->var, '=') == (int)ft_strlen(tmp->var))
				tmp->var = ft_strjoin(tmp->var, "=");
			tmp->var = ft_strjoin(tmp->var, var + i + 2);
			break ;
		}		
		tmp = tmp->next;
	}
}
