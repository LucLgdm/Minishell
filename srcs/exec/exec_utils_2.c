/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:01:52 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 12:35:32 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_stop;

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

int	exec_one_command(t_ast *node, char **paths)
{
	int	exit_status;

	if ((*get_world())->env)
		new_handle_dollar(&node->cmd, (*get_world())->env);
	else
		new_handle_dollar(&node->cmd, (*get_world())->new_env);
	ft_redirect(node);
	if (!node->cmd || !node->cmd[0])
		return (0);
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
		ft_free_array(paths);
	}
	if (g_stop)
		retval = 130;
	return (retval);
}
