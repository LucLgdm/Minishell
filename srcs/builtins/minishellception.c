/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellception.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:55:59 by andrean           #+#    #+#             */
/*   Updated: 2025/03/20 16:33:03 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_error(int file_type, char *path)
{
	ft_putstr_fd(path, 2);
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
}

int	ft_exec_file(char *path, char **args)
{
	pid_t	pid;
	int		retval;

	pid = fork();
	if (pid == -1)
		perror("");
	if (pid == 0)
	{
		execve(path, args, ft_create_envp());
		file_error(file_exists(path), path);
	}
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

int	ft_minishellception(t_ast *node)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_calloc_stop(sizeof(char *), get_arg_nb(node) + 1);
	if (!args)
		return (perror(""), 1);
	args[0] = extract_filename(node);
	if (!args[0])
		return (perror(""), 1);
	while (node->cmd[++i])
		args[i] = node->cmd[i];
	return (ft_exec_file(node->cmd[0], args));
}
