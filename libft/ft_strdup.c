/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:33:16 by andrean           #+#    #+#             */
/*   Updated: 2024/11/12 14:43:47 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char*s)
{
	size_t	i;
	size_t	slen;
	char	*dup;

	i = 0;
	slen = ft_strlen(s);
	dup = malloc(sizeof(char) * slen + 1);
	if (dup == 0)
		return (NULL);
	while (i < slen)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
