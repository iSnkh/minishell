/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 11:15:51 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/05 17:56:48 by amonteli         ###   ########lyon.fr   */
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

	env_val = extract_env_var(env_key);
	str = ft_strreplace(token->token, ft_strjoin_free(ft_strdup("$"), ft_strdup(env_key), 1), env_val);
	ft_printf("str={%s}\n", str);
	token->token = ft_strdup(str);
	free(str);
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
		replace_str(token, env_key);
}
