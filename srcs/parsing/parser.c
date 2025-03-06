/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:07 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/06 15:08:40 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_ast	*parse_token(t_token *token)
{
	t_ast	*root;

	root = NULL;
	ft_create_tree(&root, token);
	return (root);
}

void	ft_create_tree(t_ast **root, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && (tmp->token_type == TOKEN_WORD
			|| tmp->token_type == TOKEN_PARENTHESES || tmp->created))
		tmp = tmp->next;
	if (!tmp)
		*root = ft_create_cmd_solo(token);
	else
		*root = ft_create_token_node(tmp);
}
