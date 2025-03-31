/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:07 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/27 17:37:40 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_parentheses(t_token *token)
{
	t_ast	*sub_ast;
	t_redir	*redir;

	sub_ast = NULL;
	if (!token || token->token_type != TOKEN_PARENTHESES)
		return (NULL);
	if (token->sub_token)
		sub_ast = parse_token(token->sub_token);
	if (!sub_ast)
		return (NULL);
	token = token->next;
	while (token && ft_is_redir(token))
	{
		ft_handle_redir(&redir, &token, sub_ast);
		token = token->next;
		if (token)
			token = token->next;
	}
	if (token && token->token_type == TOKEN_WORD)
		ft_syntaxe_error((*get_world()));
	return (sub_ast);
}

t_token	*find_last_logical_operator(t_token *token)
{
	t_token	*last;

	last = NULL;
	while (token)
	{
		if (token->token_type == TOKEN_PIPEPIPE
			|| token->token_type == TOKEN_ANDAND)
			last = token;
		token = token->next;
	}
	return (last);
}

t_token	*find_last_pipe(t_token *token)
{
	t_token	*last;

	last = NULL;
	while (token)
	{
		if (token->token_type == TOKEN_PIPE)
			last = token;
		token = token->next;
	}
	return (last);
}

t_ast	*parse_pipes(t_token *token)
{
	t_token	*op;
	t_token	*split;
	t_ast	*node;

	op = find_last_pipe(token);
	if (op)
	{
		node = ft_new_ast(NODE_PIPE);
		free(op->value);
		op->value = NULL;
		split = split_token(token, op, NULL, NULL);
		node->left = parse_pipes(split);
		ft_free_token(&split, 0);
		node->right = parse_pipes(op->next);
		return (node);
	}
	if (token->token_type == TOKEN_PARENTHESES)
		return (parse_parentheses(token));
	return (parse_simple_command(token));
}
