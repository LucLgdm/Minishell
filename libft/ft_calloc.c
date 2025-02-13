/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 09:02:00 by andrean           #+#    #+#             */
/*   Updated: 2024/11/13 16:48:01 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	size_t	mult;
	void	*res;

	i = 0;
	mult = size * nmemb;
	if (size != 0 && mult / size != nmemb)
		return (NULL);
	res = malloc(mult);
	if (!res)
		return (NULL);
	while (i < mult)
	{
		((unsigned char *)res)[i] = 0;
		i++;
	}
	return (res);
}
