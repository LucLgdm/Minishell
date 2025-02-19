/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:44:44 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:42 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_size;
	size_t	src_size;
	size_t	i;

	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	i = -1;
	if (dest_size >= size || size == 0)
		return (size + src_size);
	else
	{
		while (++i + dest_size + 1 < size && src[i])
			dest[i + dest_size] = src[i];
	}
	dest[dest_size + i] = '\0';
	return (src_size + dest_size);
}
