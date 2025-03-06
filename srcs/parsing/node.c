/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:20:30 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/06 15:06:51 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/parsing.h"
#include "../../includes/minishell.h" // Pour print_tree

t_ast	*ft_create_token_node(t_token *token)
{
	t_ast	*root;
	t_token	*prev;
	t_token	*next;

	root = ft_new_ast(token->token_type, 0);
	printf("root_type = %i\n", root->node_type);
	token->created = 1;
	next = token->next;
	while (next && (next->created || next->token_type != TOKEN_WORD))
		next = next->next;
	printf("Next token_value = %s\n", next->value);
	prev = token;
	while (prev && (prev->created || prev->token_type != TOKEN_WORD))
		prev = prev->prev;
	printf("Prev token_value = %s\n", prev->value);
	if (prev)
		ft_create_tree(&root->left, prev);
	if (next)
		ft_create_tree(&root->right, next);

	return (root);
}

