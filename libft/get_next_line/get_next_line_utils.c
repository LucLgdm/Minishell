/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:34:53 by andrean           #+#    #+#             */
/*   Updated: 2024/12/12 09:44:28 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	freeptr(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	linechecker(t_box *box)
{
	int	i;

	i = 0;
	if (!(box->line))
	{
		box->line = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!(box->line))
			return (0);
		*(box->line) = 0;
		return (1);
	}
	while ((box->line)[i] != '\n' && (box->line)[i] != '\0')
		i++;
	if ((box->line)[i] == '\0')
		return (1);
	(box->line)[i + 1] = 0;
	if (!(box->rest))
		box->rest = "";
	return (0);
}

void	boxnuller(t_box *box)
{
	box->line = NULL;
	box->tmp = NULL;
	box->rest = NULL;
	box->nbread = 1;
}

unsigned long	ft_strlcpy(char *dst, const char *src, unsigned long siz)
{
	unsigned long int	i;

	i = 0;
	if (siz != 0)
	{
		while (src[i] && i < siz - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	while (src[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, unsigned long n)
{
	while (n)
	{
		((unsigned char *)s)[n - 1] = '\0';
		n--;
	}
}
