/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:15:51 by amonteli          #+#    #+#             */
/*   Updated: 2021/03/29 18:31:35 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_env_var(char *env_str)
{
	ft_printf("envSTR={%s}\n", env_str);
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

void	replace_str(t_token *token, int pos, char *env_key)
{
	char	*str;
	char	*env_value;
	char	*len;

	env_value = extract_env_var(env_key);
	str = ft_strreplace(token->token, ft_strjoin_free(ft_strdup("$"), ft_strdup(env_key), 1), env_value);
	ft_printf("str={%s}\n", str);
	// *token->token = &str;
	// ft_printf()
}

void	replace_env(t_list *list)
{
	t_token	*token;
	int		pos;
	char	*env_key;

	token = (t_token *)list->content;
	pos = ft_strchr_len(token->token, '$');
	env_key = ft_strndup(token->token + pos + 1, get_var_env_len(token->token + pos + 1));
	if (pos == 0 || token->token[pos - 1] != '\\') // si c'est sur que y'a pas de backslash avant go replace sans check
		replace_str(token, pos, env_key);
}

// void	replace_env222(t_list *list)
// {
// 	t_token	*token;
// 	t_list	*lst;
// 	char	*env_name;
// 	char	*replaced;
// 	int		dollar_pos;
// 	int		flags;

// 	token = (t_token *)list->content;
// 	flags = 0;
// 	dollar_pos = ft_strchr_len(token->token, '$');
// 	dollar_pos++;
// 	flags |= MS_ENV;
// 	env_name = ft_strndup(token->token + dollar_pos, get_var_env_len(token->token + dollar_pos));
// 	replaced = get_var_env(env_name);
// 	lst = ft_lstnew(create_token(replaced, flags));
	// ft_lstadd_back(&lst, ft_lstnew(create_token(token->token + dollar_pos + ft_strlen(env_name), 0)));
// 	lst_append_lsts(list, lst);
// 	free(env_name);
// }
