/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_usefull.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:59:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/27 11:39:36 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*new_node(void)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->cmd = NULL;
	new_node->token = 0;
	new_node->pipe_fd[0] = -1;
	new_node->pipe_fd[0] = -1;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	return (new_node);
}
