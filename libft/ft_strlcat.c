/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:51:04 by andrean           #+#    #+#             */
/*   Updated: 2024/11/12 12:06:08 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	long unsigned int	dstlen;
	long unsigned int	i;

	dstlen = ft_strlen(dst);
	i = 0;
	while ((dstlen + i + 1) < siz && src[i])
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	if (dstlen >= siz)
		return (ft_strlen(src) + siz);
	dst[i + dstlen] = 0;
	return (ft_strlen(src) + dstlen);
}
