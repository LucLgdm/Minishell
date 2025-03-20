/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:31:44 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 17:01:42 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_stop = 0;

int	ft_stop(void)
{
	if (g_stop)
		return (1);
	return (0);
}

void	handle_signal_afterprompt(int sig)
{
	t_world	*world;

	world = (*get_world());
	if (sig == SIGINT)
	{
		g_stop = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		free(world->prompt);
		ft_free_ast(world->tree);
		ft_free_token(world->tokenlist);
		prompt(world);
	}
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_stop = 1;
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
		return (NULL);
	exit = (void *)malloc(nmemb * size);
	if (!exit)
	{
		perror("");
		handle_signal_afterprompt(SIGINT);
		return (NULL);
	}
	ft_bzero(exit, nmemb * size);
	return (exit);
}
