/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:49:50 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:56:35 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_read_file(int fd, char *rest)
{
	char	*buffer;
	int		bytes;

	if (!rest)
		rest = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = 0;
		rest = ft_free(rest, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (rest);
}

char	*ft_free(char *buffer, char *buf)
{
	char	*tmp;

	tmp = ft_strjoin(buffer, buf);
	free(buffer);
	return (tmp);
}

char	*ft_pickline(char *rest)
{
	char	*line;
	int		i;

	i = 0;
	if (!rest[0])
		return (NULL);
	while (rest[i] && rest[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = -1;
	while (rest[++i] && rest[i] != '\n')
		line[i] = rest[i];
	if (rest[i] && rest[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*ft_update(char *rest)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	line = ft_calloc(ft_strlen(rest) - i + 1, sizeof(char));
	i++;
	j = 0;
	while (rest[i])
		line[j++] = rest[i++];
	free(rest);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest[4096];
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	rest[fd] = ft_read_file(fd, rest[fd]);
	if (!rest[fd])
		return (NULL);
	newline = ft_pickline(rest[fd]);
	rest[fd] = ft_update(rest[fd]);
	return (newline);
}
