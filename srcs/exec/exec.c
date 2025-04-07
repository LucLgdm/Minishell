/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:26:44 by andrean           #+#    #+#             */
/*   Updated: 2025/04/07 15:46:26 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_stop;

static int	ft_final_exec(char **cmd, char **paths, char **envp)
{
	char	*path;
	int		i;

	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], cmd[0]);
		if (!path)
			return (-1);
		if (!access(path, X_OK))
		{
			ft_free_array(paths);
			execve(path, cmd, envp);
		}
		free(path);
	}
	return (1);
}

void	ft_execcommand(t_ast *node, char **paths)
{
	char	**envp;
	char	**cmd;
	int		retval;

	retval = 0;
	cmd = ft_arraycpy(node->cmd);
	envp = ft_create_envp();
	free_all(get_world());
	if (!envp || !cmd)
	{
		ft_putstr_fd("malloc failed\n", 2);
		ft_free_array(envp);
		ft_free_array(cmd);
		exit_process(-1, paths);
	}
	if (paths)
		retval = ft_final_exec(cmd, paths, envp);
	if (retval == -1)
		ft_putstr_fd("malloc failed\n", 2);
	if (retval == 1)
		ft_command_not_found(cmd, paths);
	ft_free_for_exec(cmd, envp);
	exit_process(127, paths);
}

pid_t	create_process(t_ast *node, char **paths)
{
	pid_t	pid[1];
	int		*is_process;

	pid[0] = fork();
	if (pid[0] == -1)
		perror("");
	if (pid[0] == 0)
	{
		is_process = is_in_process();
		*is_process = 0;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_DFL);
		ft_execcommand(node, paths);
	}
	return (ft_check_for_stop(pid, 1));
}

static void	handle_process(int fd_0, int fd_1, t_ast *node, char **paths)
{
	int	*is_process;

	is_process = is_in_process();
	*is_process = 0;
	signal(SIGINT, SIG_IGN);
	close(fd_0);
	dup2(fd_1, STDOUT_FILENO);
	close(fd_1);
	exit_process(exec_node((*get_world()), node->left, paths), paths);
}

int	ft_do_the_pipe(t_ast *node, char **paths)
{
	int		fd[2];
	pid_t	pid[2];
	int		*is_process;

	if (pipe(fd) == -1)
		return (perror(""), -4);
	pid[0] = fork();
	if (pid[0] == -1)
		return (perror(""), -3);
	if (pid[0] == 0)
		handle_process(fd[0], fd[1], node, paths);
	close(fd[1]);
	pid[1] = fork();
	if (pid[1] == -1)
		perror("");
	if (pid[1] == 0)
	{
		is_process = is_in_process();
		*is_process = 0;
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exit_process(exec_node((*get_world()), node->right, paths), paths);
	}
	close(fd[0]);
	return (ft_check_for_stop(pid, 2));
}
