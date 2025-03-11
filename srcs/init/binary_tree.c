/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/11 13:25:45 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	fill_tree(t_world *world)
{
	t_token	*token_lst;

	token_lst = tokenization_token(world->prompt);
	if (!token_lst)
		return ;
	handle_dollar(&token_lst, world->env);
	print_token(token_lst, 0);
	world->tree = parse_token(token_lst);
	
	if (world->tree)
		print_tree(world->tree, 0);
	// 	handle_redirection(world->tree, token);
	// free_token(token);
}

// void	fill_tree(t_world *world)
// {
// 	char	**token_lst;

// 	token_lst = tokenization_char(world->prompt);
// 	if (!token_lst)
// 		return ;
		
// 	printf("Token_lst : \n");
// 	while (*token_lst)
// 	{
// 		printf("Value = %s\n", *token_lst);
// 		token_lst++;
// 	}
// 	// world->tree = parse_token(token, &i);
// 	// if (world->tree)
// 	// 	print_tree(world->tree);
// 	// 	handle_redirection(world->tree, token);
// 	// free_token(token);
// }
