/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:56:03 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/25 11:19:41 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tree_but_cmd(t_ast **root, char **cmd)
{
	if (!*root || !root)
		return ;
	ft_free_tree_but_cmd(&(*root)->left, cmd);
	ft_free_tree_but_cmd(&(*root)->right, cmd);
	if ((*root)->cmd && (*root)->cmd != cmd)
		ft_free_array((*root)->cmd);
	if ((*root)->redir)
		ft_free_redir((*root)->redir);
	free(*root);
	*root = NULL;
}

void	ft_free_for_exec(t_world	*world, char **cmd)
{
	if (world)
	{
		if (world->env)
			ft_free_hasht(world->env);
		if (world->new_env)
			ft_free_hasht(world->new_env);
		if (world->hidden_vars)
			ft_free_hasht(world->hidden_vars);
		if (world->prompt)
			free(world->prompt);
		if (world->tokenlist)
			ft_free_token(&world->tokenlist);
		if (world->tree)
			ft_free_tree_but_cmd(&(world->tree), cmd);
		free(world);
	}
}

void	free_all(t_world *world)
{
	if (world)
	{
		if (world->env)
			ft_free_hasht(world->env);
		if (world->new_env)
			ft_free_hasht(world->new_env);
		if (world->hidden_vars)
			ft_free_hasht(world->hidden_vars);
		if (world->prompt)
			free(world->prompt);
		if (world->tree)
			ft_free_ast(&world->tree);
		if (world->tokenlist)
			ft_free_token(&world->tokenlist);
		free(world);
	}
}
