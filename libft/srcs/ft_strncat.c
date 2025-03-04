/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:39:25 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/04 14:39:32 by lde-merc         ###   ########.fr       */
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
	dest_len = ft_strlen(*dest);
	src_len = ft_strnlen(src, n);
	new_str = malloc(dest_len + src_len + 1);
	if (!new_str)
		return ;
	ft_strcpy(new_str, *dest);
	ft_strlcat(new_str, src, n);
	free(*dest);
	*dest = new_str;
}
