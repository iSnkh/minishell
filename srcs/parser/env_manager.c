/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wperu <wperu@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:15:51 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/14 17:19:08 by wperu            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_env_var(char *env_str)
{
	if (!ft_strncmp("USER", env_str, 5))
		return (ft_strdup("amonteli"));
	return ("");
}

int		get_var_env_len(char *str)
{
	int		count;

	count = 0;
	while (str[count] && ft_isalnum(str[count]))
		count++;
	return (count);
}

void	replace_str(t_token *token, char *env_key)
{
	char	*str;
	char	*env_val;

	// ft_printf("token=%s\n", token->token);
	env_val = extract_env_var(env_key);
	str = ft_strreplace(token->token, ft_strjoin_free(ft_strdup("$"), ft_strdup(env_key), 1), env_val);
	token->token = ft_strdup(str);
	free(str);
}

int			get_pos_no_escaped(char *str)
{
	int		count;

	count = 0;
	while (str[count])
	{
		if (str[count] == '\\' && str[count + 1] == '$')
			count += 2;
		if (str[count] == '$')
			return (count);
		else
			count++;
	}
	return (-1);
}

void		replace_env(t_list *list)
{
	t_token	*token;
	t_list	*lst;
	int		pos;
	char	*env_key;
	//char	*str;

	token = (t_token *)list->content;
	pos = get_pos_no_escaped(token->token);
	if (pos == -1)
		return ;
	lst = ft_lstnew(create_token(ft_strndup(token->token, pos), token->flags));
	env_key = ft_strndup(token->token + pos + 1, get_var_env_len(token->token + pos + 1));
	ft_lstadd_back(&lst, ft_lstnew(create_token(extract_env_var(env_key), token->flags + MS_ENV)));
	ft_lstadd_back(&lst, ft_lstnew(create_token(token->token + pos + 1 + ft_strlen(env_key), token->flags)));
	ft_printf("pos=%d, env=%s, after=%s\n", pos, env_key, token->token + pos + 1 + ft_strlen(env_key));
	lst_append_lsts(list, lst);
	token->token = ft_strdup("");
}
