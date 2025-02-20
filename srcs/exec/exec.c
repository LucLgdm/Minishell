/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:07:29 by andrean           #+#    #+#             */
/*   Updated: 2025/02/20 16:29:52 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_execcommand(t_cmd cmd, int fd[2])
{
	char	*path;
	int		i;

	i = -1;
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	while (cmd.paths[++i])
	{
		path = ft_strjoin(cmd.paths[i], (cmd.args)[0]);
		if (!path)
			;//malloc error
		else
			execve(path, (cmd.args), getenvp());
		freetmp(&tmp, &path);
	}
	//error + exit;
}

int	create_process(t_cmd cmd, int fdin)
{
	char	*path;
	int		fd[2];
	pid_t	newpid;
	
	if (pipe(fd) == -1)
		; //pipe failure
	path = getenv("PATH");
	newpid = fork();
	if (newpid == -1)
		return (-1);
	if (newpid == 0)
	{
		ft_execcommand(cmd, fd);
		if (!path)
			;//nos commandes
	}

	close(fd[1]);
	dup2(fd[0], fdin);
	close(fd[0]);
	return (newpid);
}

int	exec_based_on_token(t_lst *word, t_lst *cmd)
{
	if (!word)
		exec_one_cmd(cmd);
	if (word->word_type == PIPE)
		exec_with_pipe(cmd);
	
}

int	exec_line(t_lst *words)
{
	t_lst	*cmd;

	if (words->word_type == 0)
		cmd = words;
	while (words && words->word_type == 0)
		words = words->next;
	
}