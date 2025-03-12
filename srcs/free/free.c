/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:56:03 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/12 16:36:51 by lde-merc         ###   ########.fr       */
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
		if (world->prompt)
			free(world->prompt);
		if (world->tree)
			ft_free_ast(world->tree);
		free(world);
	}
}
