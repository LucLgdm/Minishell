/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:39:11 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/27 15:03:16 by lde-merc         ###   ########.fr       */
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
		(*world)->env = ft_create_env_hashtable(envp);
		(*world)->new_env = NULL;
		(*world)->hidden_vars = ft_create_hidden();
		if (!(*world)->env)
			(*world)->new_env = ft_create_new_env();
		printf("\033[0;32mWelcome to Minishell!\033[0m\n");
		prompt(*world);
		free_all(world);
	}
	return (0);
}
