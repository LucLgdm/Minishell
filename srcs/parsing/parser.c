/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:07 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/11 14:45:47 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

// t_ast	*parse_token(t_token *token)
// {
// 	t_ast	*root;

// 	t_token *tmp = token;
// 	(void)tmp;
// 	root = NULL;
// 	ft_create_tree(&root, token);
// 	return (root);
// }

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

t_ast	*parse_tokens(t_token *tokens)
{
	t_token	*op;
	t_ast	*node;

	op = find_last_logical_operator(tokens);
	if (op)
	{
		node = malloc(sizeof(t_ast));
		node->node_type = (op->token_type == TOKEN_PIPEPIPE) ? NODE_OR : NODE_AND;
		op->value = NULL;
		node->left = parse_tokens(split_tokens(tokens, op));
		node->right = parse_tokens(op->next);
		return (node);
	}
	return (parse_pipes(tokens));
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
