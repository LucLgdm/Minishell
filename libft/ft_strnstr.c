/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 20:38:35 by andrean           #+#    #+#             */
/*   Updated: 2024/11/15 16:32:37 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!little[i])
		return ((char *)big);
	while (i < len && big[i])
	{
		if (((unsigned char *)big)[i] == ((unsigned char *)little)[0])
		{
			if (len - i >= ft_strlen(little))
			{
				if (ft_strncmp(big + i, little, ft_strlen(little)) == 0)
					return ((char *)big + i);
			}
		}
		i++;
	}
	return (NULL);
}
