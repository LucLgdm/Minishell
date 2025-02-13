/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:30:07 by andrean           #+#    #+#             */
/*   Updated: 2024/12/12 09:45:44 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

char	*subjoin(char *buff, unsigned long nbread, t_join *join)
{
	if (join->j < nbread)
	{
		(join->tmp) = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!(join->tmp))
			return (NULL);
		ft_strlcpy((join->tmp), buff + join->j + 1, nbread - join->j + 1);
		return (join->tmp);
	}
	(join->tmp) = (char *)malloc(sizeof(char) * 1);
	(join->tmp)[0] = 0;
	return (join->tmp);
}

char	*ft_strjoin(char **line, char *buff, unsigned long nbread)
{
	t_join	join;

	join.i = 0;
	join.j = 0;
	join.tmp = malloc(ft_strlcpy(NULL, *line, 0) + BUFFER_SIZE + 1);
	if (!(join.tmp))
		return (NULL);
	while ((*line)[join.i])
	{
		(join.tmp)[join.i] = (*line)[join.i];
		join.i++;
	}
	while (buff[join.j] && join.j < nbread && buff[join.j] != '\n')
		join.tmp[join.i++] = buff[join.j++];
	if (buff[join.j] != '\n')
		join.tmp[join.i] = 0;
	else
	{
		join.tmp[join.i] = '\n';
		join.tmp[join.i + 1] = 0;
	}
	freeptr(line);
	*line = join.tmp;
	return (subjoin(buff, nbread, &join));
}

char	*reader(t_box *box, int fd, char **buff, int freebuff)
{
	if (freebuff)
		freeptr(&(buff[fd]));
	if (freebuff)
		return (NULL);
	while (box->nbread != 0 && linechecker(box))
	{
		ft_bzero(*buff, BUFFER_SIZE + 1);
		box->nbread = read(fd, *buff, BUFFER_SIZE);
		if (box->nbread == 0 && *(box->line))
			break ;
		if (box->nbread <= 0)
		{
			freeptr(buff);
			freeptr(&(box->line));
			return (NULL);
		}
		box->rest = ft_strjoin(&(box->line), *buff, box->nbread);
		if (box->rest == NULL)
			return (NULL);
		ft_strlcpy(*buff, box->rest, ft_strlcpy(NULL, box->rest, 0) + 1);
		freeptr(&(box->rest));
	}
	if (!(**buff))
		freeptr(buff);
	return (box->line);
}

char	*get_next_line(int fd, int freebuff)
{
	static char		*buff[1024];
	t_box			box;

	if (fd < 0 || fd > 1024)
		return (NULL);
	boxnuller(&box);
	if (buff[fd] && *(buff[fd]))
	{
		box.line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		*(box.line) = 0;
		box.rest = ft_strjoin(&(box.line), buff[fd],
				ft_strlcpy(NULL, buff[fd], 0) + 1);
		ft_strlcpy(buff[fd], box.rest, ft_strlcpy(0, box.rest, 0) + 1);
		freeptr(&(box.rest));
	}
	else if (!buff[fd])
	{
		buff[fd] = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		ft_bzero(buff[fd], BUFFER_SIZE + 1);
	}
	if (!buff[fd])
		return (NULL);
	return (reader(&box, fd, &(buff[fd]), freebuff));
}
