/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:29:04 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:54:56 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*char1;
	unsigned char	*char2;
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	char1 = (unsigned char *)s1;
	char2 = (unsigned char *)s2;
	while (i < n)
	{
		if (char1[i] != char2[i])
			return (char1[i] - char2[i]);
		i++;
	}
	return (0);
}
