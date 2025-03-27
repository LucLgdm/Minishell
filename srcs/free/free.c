/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:56:03 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/27 14:30:32 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_for_exec(char **cmd, char **envp)
{
	if (cmd)
		ft_free_array(cmd);
	if (envp)
		ft_free_array(envp);
}

void	free_all(t_world **world)
{
	if (*world)
	{
		close((*world)->fd[0]);
		close((*world)->fd[1]);
		if ((*world)->env)
			ft_free_hasht((*world)->env);
		if ((*world)->new_env)
			ft_free_hasht((*world)->new_env);
		if ((*world)->hidden_vars)
			ft_free_hasht((*world)->hidden_vars);
		if ((*world)->prompt)
			free((*world)->prompt);
		if ((*world)->tree)
			ft_free_ast(&(*world)->tree);
		if ((*world)->tokenlist)
			ft_free_token(&(*world)->tokenlist, 1);
		free(*world);
		*world = NULL;
	}
}
