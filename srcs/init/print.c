/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:59:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/07 11:45:54 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tree(t_ast *ast_tree, int i)
{
	if (!ast_tree->left)
	{
		printf("~~~~~~~~~~~~~~~~~~~~ THE TREE ~~~~~~~~~~~~~~~~~~~~\n");
		if (ast_tree->cmd)
		{
			printf("Profondeur : %i, Left : %p\n", i, (void *)ast_tree->cmd);
			ft_putstr_array(ast_tree->cmd);
		}
		return ;
	}
	if (ast_tree->left)
		print_tree(ast_tree->left, i + 1);
	if (ast_tree->right->cmd)
	{
		printf("Profondeur : %i, Left : %p\n", i, (void *)ast_tree->cmd);
			ft_putstr_array(ast_tree->cmd);
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
