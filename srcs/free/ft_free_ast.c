/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:37:23 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 16:07:57 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	ft_free_ast(t_ast **root)
{
	if (!root || !*root)
		return ;
	ft_free_ast(&(*root)->left);
	ft_free_ast(&(*root)->right);
	if ((*root)->cmd)
		ft_free_array((*root)->cmd);
	if ((*root)->redir)
		ft_free_redir((*root)->redir);
	free(*root);
	*root = NULL;
}

void	ft_free_redir(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir->next;
		ft_free_array(redir->value);
		free(redir);
		redir = tmp;
	}
}
