/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:39:11 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/04 16:53:38 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_world	**world;
	int		*is_process;

	world = get_world();
	(void)argv;
	if (argc == 1)
	{
		is_process = is_in_process();
		*world = ft_calloc_stop(1, sizeof(t_world));
		(*world)->fd[0] = dup(STDIN_FILENO);
		(*world)->fd[1] = dup(STDOUT_FILENO);
		(*world)->tokenlist = NULL;
		(*world)->tree = NULL;
		ft_create_env_hashtable(envp, &(*world)->env);
		(*world)->new_env = NULL;
		ft_create_hidden(&(*world)->hidden_vars);
		if (!(*world)->env)
			ft_create_new_env(&(*world)->new_env);
		printf("\033[0;32mWelcome to Minishell!\033[0m\n");
		prompt(*world);
		free_all(world);
	}
	return (0);
}

t_world	**get_world(void)
{
	static t_world	*world;

	return (&world);
}
