/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:35:04 by andrean           #+#    #+#             */
/*   Updated: 2025/03/21 14:19:07 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_output(char *file, int fd, int append)
{
	int	newfd;

	if (append)
		newfd = open(file, O_CREAT | O_APPEND | O_WRONLY, 0644);
	else
		newfd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (newfd == -1)
		return (perror(""));
	if (dup2(newfd, fd) == -1)
		return (perror(""));
	close(newfd);
}

void	redirect_input(char *file, int *fd)
{
	int	newfd;

	newfd = open(file, O_RDONLY, 0644);
	if (newfd == -1)
		return (perror(""));
	if (*fd)
		close(*fd);
	*fd = newfd;
	// if (dup2(newfd, fd) == -1)
	// 	return (perror(""));
}

void	ft_here_doc(char *limit, int *fdin)
{
	int		herefd;
	char	*line;

	herefd = open(".heredoc", O_CREAT | O_WRONLY, 0644);
	if (herefd == -1)
		return (perror(""));
	printf("there, limit : %s, herefd: %d\n", limit, herefd);
	line = readline("heredoc>");
	while (line && ft_strcmp(line, limit))
	{
		ft_putstr_fd(line, herefd);
		ft_putstr_fd("\n", herefd);
		free(line);
		line = readline("heredoc>");
	}
	if (!line)
		return (perror(""));
	else
		free(line);
	close(herefd);
	redirect_input(".heredoc", fdin);
}
