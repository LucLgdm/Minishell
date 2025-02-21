/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:56:03 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/21 17:17:39 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_world *world)
{
	if (world)
	{
		if (world->env)
			ft_lstclear(&world->env, free);
		if (world->prompt)
			free(world->prompt);
		free(world->home);
		free(world);
	}
}
