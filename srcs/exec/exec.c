/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:07:29 by andrean           #+#    #+#             */
/*   Updated: 2025/02/26 15:56:45 by andrean          ###   ########.fr       */
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
		free(path);
	}
	//error + exit;
}

int	create_process(t_cmd cmd, int fdin)
{
	char	*path;
	int		fd[2];
	pid_t	newpid;
	
	if (g_stop)
		return (0);
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

void	exec_with_or(t_lst *cmd, int *exec_next, int fdin)
{
	exec_one_cmd(cmd, fdin);
}

void	exec_with_and(t_lst *cmd, int *exec_next, int fdin)
{
	exec_one_cmd(cmd, fdin);
}

void	exec_with_pipe(t_lst *cmd, int *exec_next, int *fdin)
{
	//redirect;
	
	*exec_next = 1;
}

int	exec_one_cmd(t_lst *word, int fdin)
{
	int		*exit_status;
	t_cmd	cmd;
	pid_t	pid;

	if (word->word_type == -1)
		return (exec_line(*(word->sub)));
	cmd.args = cmd_tab(word);
	cmd.paths = path_tab();
	pid = create_process(cmd, fdin);
	waitpid(pid, exit_status, NULL);
	if (_WIFEXITED(exit_status))
}

int	exec_based_on_token(t_lst *word, t_lst *cmd, int *exec_next, int fdin)
{
	if (!word)
		exec_one_cmd(cmd, fdin);
	if (word->word_type == PIPE)
		exec_with_pipe(cmd, *exec_next, fdin);
	if (word->word_type == AND)
		exec_with_and(cmd, *exec_next, fdin);
	if (word->word_type == OR)
		exec_with_or(cmd, *exec_next, fdin);
}

int	exec_line(t_lst *words)
{
	t_lst	*cmd;

	if (words->word_type <= 0)
		cmd = words;
	while (words && words->word_type == 0)
		words = words->next;
	
}