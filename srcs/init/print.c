/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:59:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/12 11:14:27 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tree(t_ast *ast_tree, int i)
{
	char *operator[4] = {"", "|", "&&", "||"};
	if (!ast_tree->left && !ast_tree->right){
		if (ast_tree->cmd[0])
		{
			ft_printf("Profondeur : %i, Commande : ", i);
			ft_putstr_array(ast_tree->cmd);
			printf("\n");
		}
	}
	if(ast_tree->left){
		printf("Left\n");
		print_tree(ast_tree->left, i + 1);
	}
	if (ast_tree->right){
		printf("Right\n");
		print_tree(ast_tree->right, i + 1);
	}
	if (ast_tree->node_type != NODE_CMD){
		
		printf("Profondeur : %i, Token : %s\n", i, operator[ast_tree->node_type]);
		printf("\n");
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
