/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_usefull.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:59:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/06 12:16:48 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tree(t_ast *root){
	if (!root->left && !root->right){
		printf("Commande unique\n");
		print_tab(root->cmd);
		return ;
	}
}

void print_tab(char **tab) {
    for (int i = 0; tab[i]; i++) {
        printf("%s ", tab[i]);
    }
    printf("\n");
}


void	print_token(t_token *token_lst, int i)
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
