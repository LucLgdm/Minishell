/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellception.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:55:59 by andrean           #+#    #+#             */
/*   Updated: 2025/03/27 15:30:46 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_error(int file_type, char *path)
{
	ft_putstr_fd(path, 2);
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

int	ft_exec_file(char *path, char **args)
{
	pid_t	pid;
	char	**envp;
	int		retval;

	pid = fork();
	if (pid == -1)
	{
		perror("");
		return (1);
	}
	if (pid == 0)
	{
		envp = ft_create_envp();
		free_all(get_world());
		if (!access(path, X_OK))
			execve(path, args, envp);
		file_error(file_exists(path), path);
	}
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
		return (ft_strdup_stop("/"));
	if (str)
	{
		while (str[++i])
			;
		while (str[--i] != '/')
			;
		file = ft_substr_stop(str, i, ft_strlen(str + i));
	}
	return (file);
}

int	ft_minishellception(t_ast *node)
{
	char	**args;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_calloc_stop(sizeof(char *), get_arg_nb(node) + 1);
	if (!tmp)
		return (perror(""), 1);
	tmp[0] = extract_filename(node);
	if (!tmp[0])
		return (perror(""), 1);
	while (node->cmd[++i])
		tmp[i] = node->cmd[i];
	args = ft_arraycpy_stop(tmp);
	free(tmp[0]);
	free(tmp);
	return (ft_exec_file(ft_strdup_stop(node->cmd[0]), args));
}
