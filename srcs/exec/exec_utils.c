/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:24:49 by andrean           #+#    #+#             */
/*   Updated: 2025/04/10 12:33:12 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_stop;

int	ft_redirect(t_ast *node)
{
	int		final_fdin;
	int		error;
	t_redir	*redir;

	error = 0;
	final_fdin = 0;
	redir = node->redir;
	while (redir)
	{
		if (redir->redir_type == TOKEN_LESSER)
			error += redirect_input(redir->value[0], &final_fdin);
		if (redir->redir_type == TOKEN_GREATGREATER)
			error += redirect_output(redir->value[0], STDOUT_FILENO, 1);
		if (redir->redir_type == TOKEN_GREATER)
			error += redirect_output(redir->value[0], STDOUT_FILENO, 0);
		if (redir->redir_type == TOKEN_LESSLESSER)
			error += ft_here_doc(redir->value[0], &final_fdin);
		redir = redir->next;
		if (error)
			return (0);
	}
	if (final_fdin)
		if (dup2(final_fdin, STDIN_FILENO) != -1)
			close(final_fdin);
	return (1);
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
	if (*is_in_process())
		signal(SIGQUIT, handle_sigquit);
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
	if (g_stop == 1)
		intab[1] = 130;
	signal(SIGQUIT, SIG_IGN);
	return (intab[1]);
}

static void	join_tab(char **tab)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (tab[++i])
	{
		tmp = ft_strjoin_stop(tab[i], "/");
		free(tab[i]);
		tab[i] = tmp;
	}
}

char	**path_tab(t_hashtable *hashtable)
{
	char	*path;
	char	**tab;

	path = NULL;
	if (!hashtable)
	{
		if (ft_get_element((*get_world())->new_env, "PATH"))
			path = ft_get_element((*get_world())->new_env, "PATH")->value;
		else if (ft_get_element((*get_world())->hidden_vars, "PATH"))
			path = ft_get_element((*get_world())->hidden_vars, "PATH")->value;
	}
	else if (ft_get_element(hashtable, "PATH"))
		path = ft_get_element(hashtable, "PATH")->value;
	else if (ft_get_element((*get_world())->hidden_vars, "PATH"))
		path = ft_get_element((*get_world())->hidden_vars, "PATH")->value;
	if (!path)
		return (NULL);
	tab = ft_split_stop(path, ':', 0);
	join_tab(tab);
	return (tab);
}
