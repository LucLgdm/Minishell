/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 12:20:30 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/07 16:48:10 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_ast	*ft_create_node_mandatory(t_token *token)
{
	t_ast	*root;
	
	
	return (root);
}

t_ast	*ft_create_node_bonus(t_token *token)
{
	t_ast	*root;
	int		light;

	light = 0;
	while (token->next)
		token = token->next;
	while (token->prev)
	{
		if (token->token_type == TOKEN_ANDAND)
		{
			if (light >= 0)
				light = 1;
			else
				root = ft_new_ast(TOKEN_PIPEPIPE, 0);
		}
		else if (token->token_type == TOKEN_PIPEPIPE)
		{
			if (light <= 0)
				light = -1;
			else
				root = ft_new_ast(TOKEN_ANDAND, 0);
		}
	}
	return (root);
}
