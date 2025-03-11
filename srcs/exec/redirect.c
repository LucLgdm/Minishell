/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:35:04 by andrean           #+#    #+#             */
/*   Updated: 2025/03/11 17:09:58 by andrean          ###   ########.fr       */
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
		;//error
	if (dup2(newfd, fd) == -1)
		;//error
	close(newfd);
}

void	redirect_input(char *file, int fd)
{
	int	newfd;

	newfd = open(file, O_RDONLY, 0644);
	if (newfd == -1)
		;//error
	if (dup2(newfd, fd) == -1)
		;//error
	close(newfd);
}

void	ft_here_doc(char *limit, int fdin)
{
	int		herefd;
	char	*line;
	herefd = open(".heredoc", O_CREAT | O_WRONLY, 0644);
	if(herefd == -1)
		;//error
	line = readline("heredoc>");
	while (!ft_strcmp(line, limit) && line)
	{
		ft_putstr_fd(line, herefd);
		free(line);
		line = readline("heredoc>");
	}
	if (!line)
		;//error
	else
		free(line);
	close(herefd);
	redirect_input(".heredoc", STDIN_FILENO);
}