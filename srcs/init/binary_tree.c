/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/04 15:14:41 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_token(t_token *token_lst, int i)
{
	printf("\n");
	while (token_lst){
		printf("Niveau : %i, Value = %s, Type = %i\n", i, token_lst->value, token_lst->token_type);
		if (token_lst->sub_token){
			t_token *sub_token = token_lst->sub_token;
			print_token(sub_token, i + 1);
		}
		token_lst = token_lst->next;
	}
	printf("\n");
}



void	fill_tree(t_world *world)
{
	t_token	*token_lst;

	token_lst = tokenization_token(world->prompt);
	if (!token_lst)
		return ;
	printf("Token_lst : \n");
	print_token(token_lst, 0);
	handle_dollar(&token_lst);
	print_token(token_lst, 0);
	// world->tree = parse_token(token, &i);
	// if (world->tree)
	// 	print_tree(world->tree);
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
