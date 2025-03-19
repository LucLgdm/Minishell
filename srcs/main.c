/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:39:11 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/19 14:59:33 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_world	**world;

	world = get_world();
	(void)argv;
	if (argc == 1)
	{
		*world = ft_calloc(1, sizeof(t_world));
		(*world)->env = ft_create_env_hashtable(envp);
		(*world)->new_env = NULL;
		(*world)->hidden_vars = ft_create_hidden();
		if (!(*world)->env)
			(*world)->new_env = ft_create_new_env();
		printf("\033[0;32mWelcome to Minishell!\033[0m\n");
		prompt(*world);
		free_all(*world);
	}
	return (0);
}
