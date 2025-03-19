/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:07 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/19 15:22:03 by andrean          ###   ########.fr       */
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
		split_t = split_token(token, op);
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
		node->left = parse_pipes(split_token(token, op));
		node->right = parse_pipes(op->next);
		return (node);
	}
	return (parse_simple_command(token));
}

t_ast	*parse_simple_command(t_token *token)
{
	t_ast	*node;
	t_token	*tmp;
	t_redir	*redir;
	int		i;
	int		count;

	if (!token)
		return (NULL);
	node = ft_new_ast(token->token_type);
	count = 0;
	tmp = token;
	while (tmp && tmp->token_type != TOKEN_PIPE
		&& tmp->token_type != TOKEN_ANDAND && tmp->token_type != TOKEN_PIPEPIPE)
	{
		if (tmp->token_type != TOKEN_GREATER
			&& tmp->token_type != TOKEN_GREATGREATER
			&& tmp->token_type != TOKEN_LESSLESSER
			&& tmp->token_type != TOKEN_LESSER)
			count++;
		tmp = tmp->next;
	}
	node->cmd = ft_calloc(sizeof(char *), (count + 1));
	i = 0;
	while (token && token->token_type != TOKEN_PIPE
		&& token->token_type != TOKEN_ANDAND
		&& token->token_type != TOKEN_PIPEPIPE)
	{
		if (token->token_type == TOKEN_GREATER
			|| token->token_type == TOKEN_GREATGREATER
			|| token->token_type == TOKEN_LESSER
			|| token->token_type == TOKEN_LESSLESSER)
		{
			redir = ft_calloc(sizeof(t_redir), 1);
			redir->redir_type = token->token_type;
			token = token->next;
			if (!token)
			{
				fprintf(stderr, "Erreur : redirection sans fichier\n");
				free(node);
				return (NULL);
			}
			redir->value = onelinetab(token->value);
			new_handle_dollar(&redir->value, (*get_world())->env);
			redir->next = node->redir;
			node->redir = redir;
		}
		else
			node->cmd[i++] = ft_strdup(token->value);
		token = token->next;
	}
	node->cmd[count] = NULL;
	return (node);
}

t_token	*split_token(t_token *token, t_token *op)
{
	t_token	*head;
	t_token	*tail;
	t_token	*new_token;

	if (!token || !op)
		return (NULL);
	head = NULL;
	tail = NULL;
	while (token && token != op)
	{
		new_token = malloc(sizeof(t_token));
		new_token->value = ft_strdup(token->value);
		new_token->token_type = token->token_type;
		new_token->next = NULL;
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
