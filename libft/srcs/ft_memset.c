/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:01:22 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:06 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// Pour travailler dessus
// Conversion en char

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	val;
	size_t			i;

	if (s == NULL || n == 0)
		return (s);
	ptr = s;
	val = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ptr[i] = val;
		i++;
	}
	return (s);
}
