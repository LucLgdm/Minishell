/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:26:44 by andrean           #+#    #+#             */
/*   Updated: 2025/03/10 15:00:25 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_builtins(t_ast *node)
{
	if (!strcmp(node->cmd[0], "echo"))
		ft_echo(node);
	if (!strcmp(node->cmd[0], "cd"))
		ft_cd(node);
	if (!strcmp(node->cmd[0], "pwd"))
		ft_pwd(node);
	if (!strcmp(node->cmd[0], "export"))
		ft_export(node);
	if (!strcmp(node->cmd[0], "unset"))
		ft_unset(node);
	if (!strcmp(node->cmd[0], "env"))
		ft_env(node);
	if (!strcmp(node->cmd[0], "exit"))
		ft_exit(node);
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
	int	fd[2];
	pid_t pid;
	pid_t pid2;

	if(pipe(fd) == -1)
		;//pipe failure
	pid = fork();
	if (pid == -1)
		;//fork error
	if (pid == 0)
		ft_execcommand(node, paths);
	pid2 = fork();
	if (pid2 == -1)
		;//fork error
	if (pid2 == 0)
		ft_check_for_stop(pid);
	
}

int	exec_one_command(t_ast *node, char **paths)
{
	int		*exit_status;
	pid_t	pid;

	pid = create_process(node, paths);
	waitpid(pid, exit_status, NULL);
	if (_WIFEXITED(exit_status))
}

int	exec_node(t_ast *node, char **paths)
{
	int	retval;
	
	if (!node)
		return (-1);
	retval = exec_node(node->left, paths);
	if (node->node_type == TOKEN_ANDAND)
		if (!retval)
			return (0);
	if (node->node_type == TOKEN_PIPEPIPE)
		if (retval)
			return (retval);
	if (node->node_type == TOKEN_WORD)
		exec_one_command(node, paths);
}