/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:26:44 by andrean           #+#    #+#             */
/*   Updated: 2025/03/12 14:53:29 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_builtins(t_ast *node)
{
	if (!strcmp(node->cmd[0], "echo"))
		ft_echo(node);
	else if (!strcmp(node->cmd[0], "cd"))
		ft_cd(node);
	else if (!strcmp(node->cmd[0], "pwd"))
		ft_pwd(node);
	else if (!strcmp(node->cmd[0], "export"))
		ft_export(node);
	else if (!strcmp(node->cmd[0], "unset"))
		ft_unset(node);
	else if (!strcmp(node->cmd[0], "env"))
		ft_env(node);
	else if (!strcmp(node->cmd[0], "exit"))
		ft_exit(node);
	else
		return (0);
	return (1);
}

void	ft_execcommand(t_ast *node, char **paths)
{
	char	*path;
	int		i;

	i = -1;
	if (!paths)
		get_builtins(node);
	while(paths[++i])
	{
		path = ft_strjoin(paths, node->cmd[0]);
		if (!path)
			;//malloc error
		else
			execve(path, node->cmd, getenvp());
		free(path);
	}
	//error + exit;
}

pid_t	create_process(t_ast *node, char **paths)
{
	pid_t pid[2];

	pid[0] = fork();
	if (pid[0] == -1)
		;//fork error
	if (pid[0] == 0)
		ft_execcommand(node, paths);
	pid[1] = fork();
	if (pid[1] == -1)
		;//fork error
	if (pid[1] == 0)
		ft_check_for_stop(pid, 1);
	return (pid[0]);
}

int	ft_do_the_pipe(t_ast *node, char **paths)
{
	int	fd[2];
	int	*exit_status;
	pid_t pid[3];

	if (pipe(fd) == -1)
		;//pipe failure
	pid[0] = fork();
	if (pid[0] == -1)
		; //fork error
	if (pid[0] == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(exec_node(node->left, paths));
	}
	close(fd[1]);
	pid[1] = fork();
	if (pid[1] == -1)
		;//fork error
	if (pid[1] == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exit(exec_node(node->right, paths));
	}
	close (fd[0]);
	pid[2] = fork();
	if (pid[2] == -1)
		;//fork error
	if (pid[2] == 0)
		ft_check_for_stop(pid, 2);
	waitpid(pid[2], exit_status, NULL);
	exit(exit_status);
}

int	exec_one_command(t_ast *node, char **paths)
{
	int		*exit_status;
	pid_t	pid;

	ft_redirect(node);
	if (!get_builtins(node) && paths)
	{
		pid = create_process(node, paths);
		waitpid(pid, exit_status, NULL);
		if (_WIFEXITED(exit_status))
			;
	}
}

int	exec_node(t_ast *node, char **paths)
{
	int	retval;
	int	original_stdin;
	int	original_stdout;


	if (!node)
		return (-1);
	if (node->node_type == TOKEN_PIPE)
		return (ft_do_the_pipe(node, paths));
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	retval = exec_node(node->left, paths);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	if (node->node_type == TOKEN_ANDAND)
		if (!retval)
			return (0);
	if (node->node_type == TOKEN_PIPEPIPE)
		if (retval)
			return (retval);
	if (node->node_type == TOKEN_WORD)
		return (exec_one_command(node, paths));
	return (exec_node(node->right, paths));
}