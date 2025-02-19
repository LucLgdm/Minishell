/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:40:45 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:56:08 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;
	char	*s2;

	size = ft_strlen(s) + 1;
	s2 = (char *)s;
	while (size--)
	{
		if (s2[size] == c % 256)
			return (s2 + size);
	}
	return (NULL);
}
