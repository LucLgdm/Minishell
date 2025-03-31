/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:35:04 by andrean           #+#    #+#             */
/*   Updated: 2025/03/27 14:55:16 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_output(char *file, int fd, int append)
{
	int	newfd;

	if (append)
		newfd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		newfd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (newfd == -1)
		return (perror(file), 1);
	if (dup2(newfd, fd) == -1)
		return (perror(""), 1);
	close(newfd);
	return (0);
}

int	redirect_input(char *file, int *fd)
{
	int	newfd;

	newfd = open(file, O_RDONLY, 0644);
	if (newfd == -1)
		return (perror(file), 1);
	if (*fd)
		close(*fd);
	*fd = newfd;
	return (0);
}

int	ft_here_doc(char *limit, int *fdin)
{
	int		herefd;
	char	*line;

	herefd = open(".heredoc", O_CREAT | O_WRONLY, 0644);
	if (herefd == -1)
		return (perror(""), 1);
	line = readline("heredoc>");
	while (line && ft_strcmp(line, limit))
	{
		ft_putstr_fd(line, herefd);
		ft_putstr_fd("\n", herefd);
		free(line);
		line = readline("heredoc>");
	}
	if (!line)
		ft_putstr_fd("unexpected eof\n", 2);
	else
		free(line);
	close(herefd);
	redirect_input(".heredoc", fdin);
	return (0);
}
