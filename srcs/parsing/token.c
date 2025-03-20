/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:12:49 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 15:12:28 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_token(t_token *token)
{
	t_token	*op;
	t_token	*split_t;
	t_ast	*node;

	op = find_last_logical_operator(token);
	if (op)
	{
		node = ft_new_ast(op->token_type);
		op->value = NULL;
		split_t = split_token(token, op, NULL, NULL);
		node->left = parse_token(split_t);
		if (op->next)
			node->right = parse_token(op->next);
		else
			printf("Error, manque une commande\n");
		return (node);
	}
	if (token->token_type == TOKEN_PARENTHESES)
		return (parse_parentheses(token));
	return (parse_pipes(token));
}

static void	ft_fill_new_token(t_token **new_token, t_token *token)
{
	(*new_token) = malloc(sizeof(t_token));
	(*new_token)->value = ft_strdup(token->value);
	(*new_token)->token_type = token->token_type;
	(*new_token)->next = NULL;
}

t_token	*split_token(t_token *token, t_token *op, t_token *head, t_token *tail)
{
	t_token	*new_token;

	if (!token || !op)
		return (NULL);
	new_token = NULL;
	head = NULL;
	tail = NULL;
	while (token && token != op)
	{
		ft_fill_new_token(&new_token, token);
		if (token->token_type == TOKEN_PARENTHESES)
			new_token->sub_token = token->sub_token;
		if (!head)
		{
			head = new_token;
			tail = new_token;
		}
		else
		{
			tail->next = new_token;
			tail = new_token;
		}
		token = token->next;
	}
	return (head);
}
