/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 03:09:14 by amonteli          #+#    #+#             */
/*   Updated: 2021/04/22 08:47:39 by amonteli         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		create_cmd(t_token **tokens, t_token *line, t_token *data)
{
	int				status;
	t_token			*cmd;

	status = LEXER_OK;
	ft_printf("pd de token={%s}\n", data->data);
	if ((cmd = new_token(data, T_CMD)))
	{
		cmd->next = line;
		token_add_back(tokens, cmd);
	}
	else
		status = LEXER_FALLOC;
	return (status);
}

/**
 * Create new Token
 */

t_token		*new_token(void *data, int type)
{
	t_token	*token;

	if (!(token = malloc(sizeof(*token))))
		return (NULL);
	ft_printf("ls = data={%s}\n", (char *)data);
	token->next = NULL;
	token->data = data;
	token->type = type;
	return (token);
}

/**
 * Add token to last index of the token Lst
 */

void		token_add_back(t_token **tokens, t_token *token)
{
	t_token	*current;

	if (token)
	{
		if (*tokens)
		{
			current = *tokens;
			while (current->next)
				current = current->next;
			current->next = token;
		}
		else
			*tokens = token;
	}
}

/**
 * Add token to first index of token Lst
 */

void		token_add_front(t_token **tokens, t_token *token)
{
	token->next = *tokens;
	*tokens = token;
}

/**
 * Duplicate token into memory with a size
 */

t_token		*ndup_token(const char *input, size_t n, int type)
{
	t_token	*token;
	char	*content;

	if (!(content = ft_strndup(input, n)))
		return (NULL);
	if (!(token = new_token(content, type)))
	{
		free(content);
		return (NULL);
	}
	return (token);
}

void		clear_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current)
	{
		if (current->type & T_CMD || (current->type == T_PARAM))
			clear_tokens((t_token **)&current->data);
		else
			free(current->data);
		*tokens = current->next;
		free(current);
	}
}
