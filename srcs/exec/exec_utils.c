/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:24:49 by andrean           #+#    #+#             */
/*   Updated: 2025/03/20 16:22:30 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_stop;

void	ft_redirect(t_ast *node)
{
	t_redir	*redir;

	redir = node->redir;
	while (redir)
	{
		if (redir->redir_type == TOKEN_LESSER)
			redirect_input(redir->value[0], STDIN_FILENO);
		if (redir->redir_type == TOKEN_GREATGREATER)
			redirect_output(redir->value[0], STDOUT_FILENO, 1);
		if (redir->redir_type == TOKEN_GREATER)
			redirect_output(redir->value[0], STDOUT_FILENO, 0);
		if (redir->redir_type == TOKEN_LESSLESSER)
			ft_here_doc(redir->value[0], STDIN_FILENO);
		redir = redir->next;
	}
}

static void	kill_to_stop(pid_t *pid, int pid_nb, int *intab, pid_t endpid)
{
	intab[0] = -1;
	while (++(intab[0]) < pid_nb)
		kill(pid[intab[0]], SIGTERM);
	while (1)
	{
		endpid = waitpid(-1, &intab[2], 0);
		if (endpid == pid[pid_nb - 1])
			intab[1] = intab[2];
		if (endpid == -1)
			break ;
	}
}

int	ft_check_for_stop(pid_t *pid, int pid_nb)
{
	int		intab[3];
	pid_t	endpid;

	intab[0] = 0;
	while (g_stop == 0)
	{
		endpid = waitpid(-1, &intab[2], WNOHANG);
		if (endpid)
		{
			if (endpid == pid[pid_nb - 1])
				intab[1] = intab[2] % 255;
			intab[0] += 1;
			if (intab[0] == pid_nb)
				break ;
		}
	}
	if (intab[0] != pid_nb)
		kill_to_stop(pid, pid_nb, intab, endpid);
	return (intab[1]);
}

static void	join_tab(char *tmp, char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		free(tab[i]);
		tab[i] = tmp;
	}
}

char	**path_tab(t_hashtable *hashtable)
{
	char	*path;
	char	*tmp;
	char	**tab;

	tmp = NULL;
	path = NULL;
	if (!hashtable)
	{
		if (!ft_get_element((*get_world())->new_env, "PATH"))
		{
			path = "/usr/local/sbin:/usr/local/bin";
			path = ft_strjoin(path, ":/usr/sbin:/usr/bin:/sbin:/bin");
		}
		else
			path = ft_get_element((*get_world())->new_env, "PATH")->value;
	}
	else if (ft_get_element(hashtable, "PATH"))
		path = ft_get_element(hashtable, "PATH")->value;
	if (!path)
		return (NULL);
	tab = ft_split(path, ':');
	if (!tab)
		return (NULL);
	join_tab(tmp, tab);
	return (tab);
}
