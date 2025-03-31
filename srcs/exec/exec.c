/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:26:44 by andrean           #+#    #+#             */
/*   Updated: 2025/03/27 15:01:15 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_stop;

static void	ft_command_not_found(char **cmd, char **paths)
{
	if (ft_strchr(cmd[0], '/') || !paths)
		ft_putstr_fd("no such file or directory: ", 2);
	else
		ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
}

void	ft_execcommand(t_ast *node, char **paths)
{
	char	**envp;
	char	**cmd;
	char	*path;
	int		i;

	cmd = ft_arraycpy_stop(node->cmd);
	i = -1;
	envp = ft_create_envp();
	free_all(get_world());
	if (paths)
	{
		while (paths[++i])
		{
			path = ft_strjoin_stop(paths[i], cmd[0]);
			if (!access(path, X_OK))
			{
				ft_free_array(paths);
				execve(path, cmd, envp);
			}
			free(path);
		}
	}
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
		ft_execcommand(node, paths);
	}
	return (ft_check_for_stop(pid, 1));
}

static void	handle_process(int fd_0, int fd_1, t_ast *node, char **paths)
{
	int		*is_process;

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
		perror("");
	pid[0] = fork();
	if (pid[0] == -1)
		perror("");
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
