/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/28 14:21:32 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*************************************************************************
 * Step 1 : Split the prompt into token
			"ls -l | grep txt" -> ["ls", "-l", "|", "grep", "txt", NULL]
 * Step 2 : Parsing token into a binary tree
 * Step 3 : Handling redirection
**************************************************************************/
void	fill_tree(t_world *world)
{
	t_token	*token_lst;

	token_lst = tokenization(world->prompt);
	if (!token_lst)
		return ;
		
	printf("Token_lst : \n");
	while (token_lst)
	{
		printf("Value = %s, Type = %i\n", token_lst->value, token_lst->token_type);
		token_lst = token_lst->next;
	}
	// world->tree = parse_token(token, &i);
	// if (world->tree)
	// 	print_tree(world->tree);
	// 	handle_redirection(world->tree, token);
	// free_token(token);
}
