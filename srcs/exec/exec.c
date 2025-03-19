/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:26:44 by andrean           #+#    #+#             */
/*   Updated: 2025/03/19 15:00:48 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_stop;

int	get_builtins(t_ast *node)
{
	if (!strcmp(node->cmd[0], "echo"))
		return (ft_echo(node));
	else if (!strcmp(node->cmd[0], "cd"))
		return (ft_cd(node));
	else if (!strcmp(node->cmd[0], "pwd"))
		return (ft_pwd(node));
	else if (!strcmp(node->cmd[0], "export"))
		return (ft_export(node));
	else if (!strcmp(node->cmd[0], "unset"))
		return (ft_unset(node));
	else if (!strcmp(node->cmd[0], "env"))
		return (ft_env(node));
	else if (!strcmp(node->cmd[0], "exit"))
		ft_exit(node);
	else if (ft_strchr(node->cmd[0], '/'))
		return (ft_minishellception(node));
	else
		return (-1);
	return (1);
}

void	 ft_execcommand(t_ast *node, char **paths)
{
	char	**cmd;
	char	*path;
	int		i;

	cmd = node->cmd;
	i = -1;
	if (paths)
	{
		while(paths[++i])
		{
			path = ft_strjoin(paths[i], cmd[0]);
			if (!path)
				;//malloc error
			else
				execve(path, cmd, ft_create_envp());
			free(path);
		}
	}
	if (ft_strchr(cmd[0], '/') || !paths)
		ft_putstr_fd("no such file or directory: ", 2);
	else
		ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	exit(127);
}

pid_t	create_process(t_ast *node, char **paths)
{
	pid_t pid[1];

	pid[0] = fork();
	if (pid[0] == -1)
		;//fork error
	if (pid[0] == 0)
	{
		signal(SIGINT, SIG_IGN);
		ft_execcommand(node, paths);
	}
	return (ft_check_for_stop(pid, 1));
}

int	ft_do_the_pipe(t_ast *node, char **paths)
{
	int	fd[2];
	pid_t pid[2];

	if (pipe(fd) == -1)
		;//pipe failure
	pid[0] = fork();
	if (pid[0] == -1)
		; //fork error
	if (pid[0] == 0)
	{
		signal(SIGINT, SIG_IGN);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exit(exec_node((*get_world()), node->left, paths));
	}
	close(fd[1]);
	pid[1] = fork();
	if (pid[1] == -1)
		;//fork error
	if (pid[1] == 0)
	{
		signal(SIGINT, SIG_IGN);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exit(exec_node((*get_world()), node->right, paths));
	}
	close (fd[0]);
	return(ft_check_for_stop(pid, 2));
}

int	exec_one_command(t_ast *node, char **paths)
{
	int		exit_status;

	if ((*get_world())->env)
		new_handle_dollar(&node->cmd, (*get_world())->env);
	else
		new_handle_dollar(&node->cmd, (*get_world())->new_env);
	if (!node->cmd || !node->cmd[0])
		return (0);
	ft_redirect(node);
	exit_status = get_builtins(node);
	if (exit_status == -1)
		exit_status = create_process(node, paths);
	return (exit_status);
}

int	exec_node(t_world *world, t_ast *node, char **paths)
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
	retval = exec_tree(world, node->left);
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	if (node->node_type == TOKEN_ANDAND)
		if (retval)
			return (0);
	if (node->node_type == TOKEN_PIPEPIPE)
		if (!retval)
			return (retval);
	if (node->node_type == TOKEN_WORD)
		return (exec_one_command(node, paths));
	return (exec_tree(world, node->right));
}

int	exec_tree(t_world *world, t_ast *node)
{
	int		retval;
	int		original_stdin;
	int		original_stdout;
	char	**paths;

	if (!node)
		return (-1);
	if (!g_stop)
	{
		paths = path_tab(world->env);
		original_stdin = dup(STDIN_FILENO);
		original_stdout = dup(STDOUT_FILENO);
		retval = exec_node(world, node, paths);
		dup2(original_stdin, STDIN_FILENO);
		dup2(original_stdout, STDOUT_FILENO);
		ft_modify_value(world->hidden_vars, "?", ft_itoa(retval), 0);
	}
	if (g_stop)
		retval = 130;
	return (retval);
}
