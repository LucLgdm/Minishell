/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:31:44 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 08:32:23 by lde-merc         ###   ########.fr       */
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
	if (sig == SIGINT)
	{
		g_stop = 1;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
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
