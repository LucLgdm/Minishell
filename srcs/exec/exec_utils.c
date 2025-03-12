/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:24:49 by andrean           #+#    #+#             */
/*   Updated: 2025/03/12 17:24:42 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect(t_ast *node)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir)
	{
		if (redir->redir_type == REDIR_IN)
			redirect_input(redir->value, STDIN_FILENO);
		if (redir->redir_type == REDIR_APPEND_OUT)
			redirect_output(redir->value, STDOUT_FILENO, 1);
		if (redir->redir_type == REDIR_OUT)
			redirect_output(redir->value, STDOUT_FILENO, 0);
		if (redir->redir_type == REDIR_HEREDOC)
			ft_here_doc(redir->value, STDIN_FILENO);
		redir = redir->next;
	}
}

void	ft_check_for_stop(pid_t *pid, int pid_nb)
{
	int		i;
	int		exit_status;
	int		*tmp;
	pid_t	endpid;
	int		g_stop;
	
	i = 0;
	while (g_stop == 0)
	{
		if (endpid = waitpid(-1, tmp, WNOHANG))
		{
			if (endpid == pid[pid_nb])
				exit_status = *tmp;
			i++;
			if (i == pid_nb)
				break ;
		}
	}
	if (i != pid_nb)
	{
		i = -1;
		while (++i < pid_nb)
			kill(pid[i], SIGTERM);
		while (endpid = wait(NULL))
			if (endpid == pid[pid_nb])
				exit_status = *tmp;
	}
	exit(exit_status);
}

char	**path_tab(t_hashtable hashtable)
{
	char	*path;
	char	*tmp;
	char	**tab;
	int		i;

	i = -1;
	path = ft_get_element(&hashtable, "PATH")->value;
	if (!path)
		return (NULL);
	tab = ft_split(path, ':');
	if (!tab)
		;//malloc error
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		free(tab[i]);
		tab[i] = tmp;
	}
}
