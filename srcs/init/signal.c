/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:31:44 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/07 16:06:22 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_stop = 0;

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quitted", 2);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

void	handle_signal_afterprompt(int sig)
{
	t_world	*world;

	world = (*get_world());
	if (sig == SIGINT)
	{
		if (*is_in_process())
		{
			g_stop = 1;
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
		}
		else
			g_stop = 1;
	}
}

void	stop_when_calloc_fail(void)
{
	t_world	*world;

	world = (*get_world());
	ft_putstr_fd("Malloc failed\n", 2);
	if ((*is_in_process()))
	{
		g_stop = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		free(world->prompt);
		ft_free_ast(&world->tree);
		ft_free_token(&world->tokenlist, 1);
		prompt(world);
	}
	else
		exit_process(1, NULL);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_stop = 1;
		ft_modify_value((*get_world())->hidden_vars, "?", "130", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	*ft_calloc_stop(size_t nmemb, size_t size)
{
	void	*exit;

	if (size && (nmemb > SIZE_MAX / size))
	{
		stop_when_calloc_fail();
		return (NULL);
	}
	exit = (void *)malloc(nmemb * size);
	if (!exit)
	{
		stop_when_calloc_fail();
		return (NULL);
	}
	ft_bzero(exit, nmemb * size);
	return (exit);
}
