/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   formater.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: amonteli <amontelimart@gmail.com>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2021/03/25 19:03:28 by amonteli     #+#   ##    ##    #+#       */
/*   Updated: 2021/04/16 15:32:22 by amonteli    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
#include "minishell.h"


int			has_dollar(char *str)
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

void	cmd_replace_env(t_cmd *cmd)
{
	t_list	*list;
	t_token	*token;

	list = cmd->args;
	while (list)
	{
		token = (t_token *)list->content;
		while (has_dollar(token->token) != -1 && !(token->flags & MS_SLASH || token->flags & MS_QUOTES))
		{
			replace_env(list);
		}
		list = list->next;
	}
}

char	*remove_char(char *src, char c)
{
	int		count;
	char	*str;

	count = 0;
	if (!ft_strchr(src, c))
		return (ft_strdup(src));
	count = ft_strchr_len(src, c);
	str = ft_strjoin_free(ft_strndup(src, count), ft_strdup(src + count), 1);
	return (str);
}

void	token_remove_slash(t_token *token)
{
	int		count;
	int		strc;
	char	*str;

	count = 0;
	strc = 0;
	str = ft_calloc(ft_strlen(token->token) + 1, sizeof(char));
	ft_printf("token={%s}\n", token->token);
	while (token->token[count])
	{
		if (token->token[count] == '\\')
		{
			if (ft_strchr(DQUOTE_EFFECT, token->token[count + 1]))
			{
				str[strc] = token->token[count + 1];
				strc++;
				count++;
			}
			else
			{
				str[strc] = token->token[count];
				strc++;
			}
		}
		else
		{
			str[strc] = token->token[count];
			strc++;
		}
		count++;
	}
	token->token = ft_strdup(str);
	free(str);
}

void	cmd_replace_slash(t_cmd *cmd)
{
	t_list	*list;
	t_token	*token;

	list = cmd->args;
	while (list)
	{
		token = (t_token *)list->content;
		if (ft_strchr(token->token, '\\') && !(token->flags & MS_SLASH || token->flags & MS_QUOTES))
		{
			token_remove_slash(token);
		}
		list = list->next;
	}
}

void	lst_del_next(t_list *list)
{

}

void	cmd_remove_useless_node(t_cmd *cmd)
{
	t_list	*cmdArgs;
	t_list	*nextArgs;
	t_token	*token;

	ft_printf("first_token={%s}\n", ((t_token *)cmd->args->content)->token);
}

void	format_commands(void)
{
	t_list	*cmds;
	t_cmd	*cmd;

	cmds = ms->cmds;
	ft_lstclear(&ms->tokens, free);
	while (cmds)
	{
		cmd = (t_cmd *)cmds->content;
		// cmd_split_space(cmd);
		cmd_replace_env(cmd);
		cmd_replace_slash(cmd);
		// cmd_remove_useless_node(cmd);


		//
		//
		//
		// cmd_replace_slash(cmd);
		//	FORMAT SPACES
		//	SET ARG 0 TO CMD NAME & SET FLAG PARSED
		//	EXEC

		cmds = cmds->next;
	}
	ft_lstmap(ms->tokens, &print_tokens, NULL);
}

