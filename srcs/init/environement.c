/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:17:24 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/27 12:19:04 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_env(t_list **list, char **envp, t_world *world)
{
	int		i;
	char	*home_value;

	i = -1;
	while (envp[++i] != NULL)
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(envp[i])));
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			home_value = envp[i] + 5;
			world->home = ft_strdup(home_value);
		}
	}
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
void	prompt(t_world *world)
{
	while (42)
	{
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);
		world->prompt = readline("\001\033[3;33m\002Minishell > \001\033[0m\002 ");
		if (!world->prompt || (strcmp(world->prompt, "exit") == 0))
		{
			printf("\033[0;32mFrom Minishell with Love !\033[0m\n");
			break ;
		}
		if (ft_strlen(world->prompt) > 0)
		{
			add_history(world->prompt);
			if (strcmp(world->prompt, "clean") == 0)
			{
				rl_clear_history();
				printf("\033[0;32mHistory cleaned\033[0m\n");
			}
			else
				fill_tree(world);
		}
		free(world->prompt);
	}
}
