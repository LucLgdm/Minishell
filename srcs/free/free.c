/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:56:03 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/05 10:44:21 by lde-merc         ###   ########.fr       */
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
		{
			while(++i < world->env->length)
			{
				if (world->env->table[i])
				{
					free(world->env->table[i]->key);
					free(world->env->table[i]->value);
					if (world->env->table[i]->next)
						free(world->env->table[i]->next);
					free(world->env->table[i]);
				}
			}
			free(world->env->table);
			free(world->env);
		}
		if (world->prompt)
			free(world->prompt);
		free(world);
	}
}
