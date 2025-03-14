/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:56:03 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/14 15:30:28 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_world *world)
{
	int	i;

	i = -1;
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
			ft_free_ast(world->tree);
		free(world);
	}
}
