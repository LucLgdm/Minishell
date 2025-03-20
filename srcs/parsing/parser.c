/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:07 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 16:39:00 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_parentheses(t_token *token)
{
	t_ast	*sub_ast;

	if (!token || token->token_type != TOKEN_PARENTHESES)
		return (NULL);
	if (token->sub_token)
	{
		sub_ast = parse_token(token->sub_token);
		if (sub_ast)
			return (sub_ast);
	}
	return (NULL);
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
	t_ast	*node;

	op = find_last_pipe(token);
	if (op)
	{
		node = malloc(sizeof(t_ast));
		node->node_type = NODE_PIPE;
		op->value = NULL;
		node->left = parse_pipes(split_token(token, op, NULL, NULL));
		node->right = parse_pipes(op->next);
		return (node);
	}
	return (parse_simple_command(token));
}
