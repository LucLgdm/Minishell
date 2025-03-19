/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:59:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/19 11:44:32 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	print_tree(t_ast *ast_tree, int i)
// {
// 	char *operator[4] = {"", "|", "&&", "||"};
// 	char *redir[4] = {">", ">>", "<", "<<"};
// 	if (!ast_tree->left && !ast_tree->right){
// 		if (ast_tree->cmd)
// 		{
// 			ft_printf("Profondeur : %i, Commande : ", i);
// 			ft_putstr_array(ast_tree->cmd);
// 			if (ast_tree->redir){
// 				t_redir *tmp_red = ast_tree->redir;
// 				while(tmp_red){
// 					printf("Redirection : %s, vers : %s\n", redir[tmp_red->redir_type - 5], tmp_red->value);
// 					tmp_red = tmp_red->next;
// 				}
// 			}
// 			printf("\n");
// 		}
// 		return ;
// 	}
	
// 	if(ast_tree->left){
// 		printf("Left\n");
// 		print_tree(ast_tree->left, i + 1);
// 	}
// 	if (ast_tree->right){
// 		printf("Right\n");
// 		print_tree(ast_tree->right, i + 1);
// 	}
// 	if (ast_tree->node_type >= 1 && ast_tree->node_type <= 3){
		
// 		printf("Profondeur : %i, Token : %s\n", i, operator[ast_tree->node_type]);
// 		printf("\n");
// 	}
// }


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
			printf("Token_type parentheses = %i\n", token_lst->token_type);
			printf("Sub_token = %p\n", (void *)token_lst->sub_token);
			print_token(sub_token, i + 1);
		}
		token_lst = token_lst->next;
	}
	printf("\n");
}
