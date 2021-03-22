/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:15:51 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/22 17:17:18 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_env(char *env_str)
{
	ft_printf("envSTR={%s}\n", env_str);
	if (!ft_strncmp("USER", env_str, 5))
		return (ft_strdup("amonteli"));
	return (NULL);
}

int		get_var_env_len(char *str)
{
	// ft_printf("[%s]\n", str);
	int		count;
	int		ok;

	ok = 0;
	count = 0;
	while (str[count] && !ok)
	{
		if (str[count] == ' ')
			ok = 1;
		count++;
	}
	return (count - ok);
}

void	replace_env(t_list *list)
{
	t_token	*token;
	t_list	*lst;
	char	*env_name;
	char	*replaced;
	int		dollar_pos;
	int		flags;

	token = (t_token *)list->content;
	flags = 0;
	dollar_pos = ft_strchr_len(token->token, '$');
	dollar_pos++;
	flags |= MS_ENV;
	env_name = ft_strndup(token->token + dollar_pos, get_var_env_len(token->token + dollar_pos));
	replaced = get_var_env(env_name);
	lst = ft_lstnew(create_token(replaced, flags));
	ft_lstadd_back(&lst, ft_lstnew(create_token(token->token + dollar_pos + ft_strlen(env_name), 0)));
	lst_append_lsts(list, lst);
	free(env_name);
}
