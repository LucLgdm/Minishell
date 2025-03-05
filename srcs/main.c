/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:39:11 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/05 14:52:29 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_world	*world;

	world = get_world();
	(void)argv;
	if (argc == 1)
	{
		world = ft_calloc(1, sizeof(t_world));
		world->env = ft_create_env_hashtable(envp);
		prompt(world);
		free_all(world);
	}
	return (0);
}
