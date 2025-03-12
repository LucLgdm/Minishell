/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:07 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/12 11:04:33 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_ast	*parse_token(t_token *token)
{
	t_token	*op;
	t_ast	*node;

	op = find_last_logical_operator(token);
	if (op)
	{
		node = malloc(sizeof(t_ast));
		node->node_type = (op->token_type == TOKEN_PIPEPIPE) ? NODE_OR : NODE_AND;
		op->value = NULL;
		node->left = parse_token(split_token(token, op));
		node->right = parse_token(op->next);
		return (node);
	}
	return (parse_pipes(token));
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
	int		count;
	t_token	*tmp;

	if (!token)
		return (NULL);
	node = malloc(sizeof(t_ast));
	node->node_type = NODE_CMD;
	count = 0;
	tmp = token;
	while (tmp && tmp->token_type != TOKEN_PIPE
		&& tmp->token_type != TOKEN_ANDAND && tmp->token_type != TOKEN_PIPEPIPE)
	{
		count++;
		tmp = tmp->next;
	}
	node->cmd = malloc(sizeof(char *) * (count + 1));
	for (int i = 0; i < count; i++)
	{
		node->cmd[i] = ft_strdup(token->value);
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

// void	ft_create_tree(t_ast **root, t_token *token)
// {
// 	t_token	*tmp;
// 	bool	dp_de;

// 	dp_de = false;
// 	tmp = token;
// 	while (tmp->next)
// 	{
// 		if (tmp->token_type == TOKEN_ANDAND
// 			|| tmp->token_type == TOKEN_PIPEPIPE)
// 		{
// 			dp_de = true;
// 			break ;
// 		}
// 		tmp = tmp->next;
// 	}
// 	if (dp_de)
// 	{
// 		*root = ft_create_node_bonus(tmp);
// 		ft_create_tree((*root)->left, tmp->next);
// 		ft_create_tree((*root)->right, token);
// 	}
// 	else
// 	{
// 		if ()
// 		*root = ft_create_node_mandatory(token);
// 	}
// }

// void	ft_create_tree(t_ast **root, t_token *token)
// {
// 	t_token	*tmp;

// 	tmp = token;
// 	while (tmp && (tmp->token_type == TOKEN_WORD
// 			|| tmp->token_type == TOKEN_PARENTHESES || tmp->created))
// 		tmp = tmp->next;
// 	if (!tmp)
// 		*root = ft_create_cmd_solo(token);
// 	else
// 		*root = ft_create_token_node(tmp);
// }
