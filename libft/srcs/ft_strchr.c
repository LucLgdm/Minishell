/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:02:14 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:29 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	size;
	char	*s2;

	i = 0;
	size = ft_strlen(s) + 1;
	s2 = (char *)s;
	while (i < size)
	{
		if (s2[i] == c % 256)
			return (s2 + i);
		i++;
	}
	return (NULL);
}
