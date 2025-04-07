/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:12:49 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/07 12:48:49 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*parse_token(t_token *token, t_ast **node)
{
	t_token	*op;
	t_token	*split_t;

	op = find_last_logical_operator(token);
	if (op)
	{
		*node = ft_new_ast(op->token_type);
		free(op->value);
		op->value = NULL;
		split_t = split_token(token, op, NULL, NULL);
		(*node)->left = parse_token(split_t, &(*node)->left);
		ft_free_token(&split_t, 0);
		if (op->next)
			(*node)->right = parse_token(op->next, &(*node)->right);
		else
			printf("Error, manque une commande\n");
		return (*node);
	}
	return (parse_pipes(token, node));
}

static void	ft_fill_new_token(t_token **new_token, t_token *token)
{
	(*new_token) = ft_calloc(sizeof(t_token), 1);
	if (!*new_token)
		return ;
	(*new_token)->value = ft_strdup(token->value);
	if (!(*new_token)->value)
	{
		free(*new_token);
		*new_token = NULL;
		return ;
	}
	(*new_token)->token_type = token->token_type;
	(*new_token)->sub_token = NULL;
	(*new_token)->next = NULL;
}

t_token	*split_token(t_token *token, t_token *op, t_token *head, t_token *tail)
{
	t_token	*new_token;

	if (!token || !op)
		return (NULL);
	new_token = NULL;
	while (token && token != op)
	{
		ft_fill_new_token(&new_token, token);
		if (!new_token)
			return (ft_free_token(&head, 0), NULL);
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
