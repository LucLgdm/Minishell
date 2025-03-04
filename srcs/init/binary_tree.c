/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/04 09:12:08 by lde-merc         ###   ########.fr       */
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

	token_lst = tokenization_token(world->prompt);
	if (!token_lst)
		return ;
		
	printf("Token_lst : \n");
	while (token_lst)
	{
		printf("Value = %s, Type = %i\n", token_lst->value, token_lst->token_type);
		if (token_lst->sub_token)
		{
			printf("	Sub_token : \n");
			t_token *sub_token = token_lst->sub_token;
			while (sub_token)
			{
				printf("	Value = %s, Type = %i\n", sub_token->value, sub_token->token_type);
				if (sub_token->sub_token){
					printf("		Sub_token : \n");
					t_token *sub_sub_token = sub_token->sub_token;
					while (sub_sub_token)
					{
						printf("		Value = %s, Type = %i\n", sub_sub_token->value, sub_sub_token->token_type);
						sub_sub_token = sub_sub_token->next;
					}
				}
				sub_token = sub_token->next;
			}
		}
		token_lst = token_lst->next;
	}
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
