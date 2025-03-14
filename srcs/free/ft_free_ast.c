/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:37:23 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/12 17:05:11 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	ft_free_ast(t_ast *root)
{
	if (!root)
		return ;
	ft_free_ast(root->left);
	ft_free_ast(root->right);
	if (root->cmd)
		ft_free_array(root->cmd);
	if (root->redir)
		ft_free_redir(root->redir);
	free(root);
}

void	ft_free_redir(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir->next;
	free(redir->value);
	free(redir);
	redir = tmp;
}
