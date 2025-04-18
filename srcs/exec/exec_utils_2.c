/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:01:52 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/07 16:05:47 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_stop;

char	*ft_strchr_outofquotes(char *str, char c)
{
	int	i;

	i = 0;
	if (!c || !str)
		return (str);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			quotes(str, &i, NULL, str[i]);
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

int	get_builtins(t_ast *node, char **paths)
{
	if (!ft_strcmp(node->cmd[0], "echo"))
		return (ft_echo(node));
	else if (!ft_strcmp(node->cmd[0], "cd"))
		return (ft_cd(node));
	else if (!ft_strcmp(node->cmd[0], "pwd"))
		return (ft_pwd(node));
	else if (!ft_strcmp(node->cmd[0], "export"))
		return (ft_export(node));
	else if (!ft_strcmp(node->cmd[0], "unset"))
		return (ft_unset(node));
	else if (!ft_strcmp(node->cmd[0], "env"))
		return (ft_env(node));
	else if (!ft_strcmp(node->cmd[0], "exit"))
		return (ft_exit(node, paths), 1);
	else if (ft_strchr(node->cmd[0], '/'))
		return (ft_minishellception(node, paths));
	else if (!ft_strcmp(node->cmd[0], "yes"))
		return (ft_no_yes_here(node));
	return (-2);
}

int	exec_one_command(t_ast *node, char **paths)
{
	int	exit_status;

	if ((*get_world())->env)
		new_handle_dollar(&node->cmd, (*get_world())->env);
	else
		new_handle_dollar(&node->cmd, (*get_world())->new_env);
	if (!node->cmd || !node->cmd[0])
		return (0);
	exit_status = get_builtins(node, paths);
	if (exit_status == -1)
	{
		ft_free_array(paths);
		return (exit_status);
	}
	if (exit_status == -2)
		exit_status = create_process(node, paths);
	return (exit_status);
}

int	exec_node(t_world *world, t_ast *node, char **paths)
{
	int	retval;

	if (!node)
		return (-1);
	if (!ft_redirect(node))
		return (1);
	if (node->node_type == TOKEN_PIPE)
		return (ft_do_the_pipe(node, paths));
	retval = exec_tree(world, node->left, 0);
	if (node->node_type == TOKEN_ANDAND)
		if (retval)
			return (retval);
	if (node->node_type == TOKEN_PIPEPIPE)
		if (!retval)
			return (retval);
	if (node->node_type == TOKEN_WORD)
		return (exec_one_command(node, paths));
	return (exec_tree(world, node->right, 1));
}

int	exec_tree(t_world *world, t_ast *node, int reset)
{
	int		retval;
	char	**paths;
	char	*char_retval;

	if (!node)
		return (-1);
	if (!g_stop)
	{
		paths = path_tab(world->env);
		retval = exec_node(world, node, paths);
		if (reset)
		{
			dup2(world->fd[0], STDIN_FILENO);
			dup2(world->fd[1], STDOUT_FILENO);
		}
		ft_free_array(paths);
		char_retval = ft_itoa_stop(retval);
		ft_modify_value(world->hidden_vars, "?", char_retval, 0);
		free(char_retval);
	}
	if (g_stop)
		retval = 130;
	return (retval);
}
