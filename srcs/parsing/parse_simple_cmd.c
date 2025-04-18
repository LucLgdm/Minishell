/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:13:39 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/04 16:47:41 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_isoperator(int type)
{
	return (type == TOKEN_GREATER || type == TOKEN_GREATGREATER
		|| type == TOKEN_LESSER || type == TOKEN_LESSLESSER);
}

static bool	ft_is_token(int type)
{
	return (type == TOKEN_PIPE || type == TOKEN_PIPEPIPE
		|| type == TOKEN_ANDAND);
}

void	ft_handle_redir(t_redir **redir, t_token **token, t_ast **node)
{
	t_redir	*tmp;

	*redir = ft_calloc_stop(sizeof(t_redir), 1);
	(*redir)->redir_type = (*token)->token_type;
	*token = (*token)->next;
	if (!token)
		return (perror("Error in redirection"), free(node));
	(*redir)->value = onelinetab((*token)->value);
	if (!(*redir)->value)
	{
		free(*redir);
		stop_when_calloc_fail();
	}
	new_handle_dollar(&(*redir)->value, (*get_world())->env);
	if (!(*node)->redir)
		(*node)->redir = *redir;
	else
	{
		tmp = (*node)->redir;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = *redir;
	}
}

static void	ft_do_something(t_token **tmp, int *count)
{
	if (!ft_isoperator((*tmp)->token_type))
		(*count)++;
	(*tmp) = (*tmp)->next;
}

t_ast	*parse_simple_command(t_token *token, t_ast **node)
{
	t_token	*tmp;
	t_redir	*redir;
	int		i;
	int		count;

	redir = NULL;
	if (!token)
		return (NULL);
	*node = ft_new_ast(token->token_type);
	count = 0;
	tmp = token;
	while (tmp && !ft_is_token(tmp->token_type))
		ft_do_something(&tmp, &count);
	i = 0;
	(*node)->cmd = ft_calloc_stop(sizeof(char *), (count + 1));
	while (token && !ft_is_token(token->token_type))
	{
		if (ft_isoperator(token->token_type))
			ft_handle_redir(&redir, &token, node);
		else
			(*node)->cmd[i++] = ft_strdup_stop(token->value);
		token = token->next;
	}
	return (*node);
}
