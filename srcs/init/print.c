/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:59:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 09:20:06 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_print_tree_2(t_ast *ast_tree, char **redir, int i)
{
	t_redir	*tmp_red;

	if (!ast_tree->left && !ast_tree->right)
	{
		if (ast_tree->cmd)
		{
			ft_printf("Profondeur : %i, token : %d, Commande : ", i,
				ast_tree->node_type);
			ft_putstr_array(ast_tree->cmd);
			if (ast_tree->redir)
			{
				tmp_red = ast_tree->redir;
				while (tmp_red)
				{
					printf("Redirection : %s, vers : \n",
						redir[tmp_red->redir_type - 5]);
					ft_print_tab(tmp_red->value);
					tmp_red = tmp_red->next;
				}
			}
			printf("\n");
		}
		return ;
	}
}

static void	ft_print_tree_3(t_ast *ast_tree, char **operator, int i)
{
	if (ast_tree->left)
	{
		printf("Left\n");
		print_tree(ast_tree->left, i + 1);
	}
	if (ast_tree->right)
	{
		printf("Right\n");
		print_tree(ast_tree->right, i + 1);
	}
	if (ast_tree->node_type >= 1 && ast_tree->node_type <= 3)
	{
		printf("Profondeur : %i, Token : %s\n", i,
			operator[ast_tree->node_type]);
		printf("\n");
	}
}

void	print_tree(t_ast *ast_tree, int i)
{
	char	*operator[4];
	char	*redir[4];

	operator[0] = "";
	operator[1] = "|";
	operator[2] = "&&";
	operator[3] = "||";
	redir[0] = ">";
	redir[1] = ">>";
	redir[2] = "<";
	redir[3] = "<<";
	ft_print_tree_2(ast_tree, redir, i);
	ft_print_tree_3(ast_tree, operator, i);
}

void	print_token(t_token *token_lst, int i)
{
	t_token	*sub_token;

	printf("\n");
	while (token_lst)
	{
		printf("Niveau : %i, Value = %s, Type = %i\n", i, token_lst->value,
			token_lst->token_type);
		if (token_lst->sub_token)
		{
			sub_token = token_lst->sub_token;
			printf("Token_type parentheses = %i\n", token_lst->token_type);
			printf("Sub_token = %p\n", (void *)token_lst->sub_token);
			print_token(sub_token, i + 1);
		}
		token_lst = token_lst->next;
	}
	printf("\n");
}

void	ft_print_env(t_hashtable *env)
{
	int			i;
	t_element	*tmp;

	if (!env || !env->table)
		return ;
	i = -1;
	while (++i < env->length)
	{
		tmp = env->table[i];
		while (tmp)
		{
			ft_printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
}
