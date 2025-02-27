/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/27 14:19:23 by lde-merc         ###   ########.fr       */
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
	char	**token;

	token = tokenization(world->prompt);
	if (!token)
		return ;
	int i = -1;
	printf("Token : \n");
	while(token[++i]){
		printf("i = %i, token = %s\n", i, token[i]);
	}
	// world->tree = parse_token(token);
	// if (world->tree)
	// 	handle_redirection(world->tree, token);
	// free_token(token);
}

