/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellception.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:55:59 by andrean           #+#    #+#             */
/*   Updated: 2025/04/04 14:38:16 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_error(int file_type, char *path)
{
	ft_putstr_fd(path, 2);
	free_all(get_world());
	free(path);
	if (file_type == 0)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
	}
	if (file_type == 4)
	{
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (file_type == 8)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
	exit(126);
}

static void	ft_child(char **paths, char **envp, char **args, char *path)
{
	ft_free_array(paths);
	envp = ft_create_envp();
	free_all(get_world());
	if (!access(path, X_OK))
		execve(path, args, envp);
	ft_free_array(envp);
	ft_free_array(args);
	file_error(file_exists(path), path);
}

int	ft_exec_file(char *path, char **args, char **paths)
{
	pid_t	pid;
	char	**envp;
	int		retval;

	envp = NULL;
	if (!path)
		return (ft_free_array(args), -1);
	pid = fork();
	if (pid == -1)
		return (perror(""), 1);
	if (pid == 0)
		ft_child(paths, envp, args, path);
	ft_free_array(args);
	free(path);
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &retval, 0);
	signal(SIGINT, handle_signal_afterprompt);
	return (retval % 255);
}

char	*extract_filename(t_ast *node)
{
	char	*str;
	char	*file;
	int		i;

	i = -1;
	file = NULL;
	str = node->cmd[0];
	if (ft_strcmp(str, "/") == 0)
		return (ft_strdup("/"));
	if (str)
	{
		while (str[++i])
			;
		while (str[--i] != '/')
			;
		file = ft_substr(str, i, ft_strlen(str + i));
	}
	return (file);
}

int	ft_minishellception(t_ast *node, char **paths)
{
	char	**args;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc(sizeof(char *), get_arg_nb(node) + 1);
	if (!tmp)
		return (-1);
	tmp[0] = extract_filename(node);
	if (!tmp[0])
		return (-1);
	while (node->cmd[++i])
		tmp[i] = node->cmd[i];
	args = ft_arraycpy(tmp);
	free(tmp[0]);
	free(tmp);
	if (!args)
		return (-1);
	return (ft_exec_file(ft_strdup(node->cmd[0]), args, paths));
}
