/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:39:25 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/18 12:30:49 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_strncat(char **dest, const char *src, size_t n)
{
	size_t	dest_len;
	size_t	src_len;
	char	*new_str;

	if (!src || n == 0)
		return ;
	if (*dest)
		dest_len = ft_strlen(*dest);
	else
		dest_len = 0;
	src_len = ft_strnlen(src, n);
	new_str = ft_calloc(dest_len + src_len + 1, 1);
	if (!new_str)
		return ;
	if (*dest)
		ft_strcpy(new_str, *dest);
	ft_strlcat(new_str, src, dest_len + src_len + 1);
	free(*dest);
	*dest = new_str;
}
