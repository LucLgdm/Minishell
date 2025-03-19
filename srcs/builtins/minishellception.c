/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellception.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:55:59 by andrean           #+#    #+#             */
/*   Updated: 2025/03/19 15:00:06 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_file(char *path, char **args)
{
	pid_t	pid;
	int		retval;

	pid = fork();
	if (pid == -1)
		;//fork error
	if (pid == 0)
	{
		execve(path, args, ft_create_envp());
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(127);
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
	args = ft_calloc(sizeof(char *), get_arg_nb(node) + 1);
	if (!args)
		;//malloc error
	args[0] = extract_filename(node);
	if (!args[0])
		;//malloc error
	while (node->cmd[++i])
		args[i] = node->cmd[i];
	return (ft_exec_file(node->cmd[0], args));
}
