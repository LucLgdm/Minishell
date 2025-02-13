/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:01:56 by andrean           #+#    #+#             */
/*   Updated: 2024/11/19 10:10:50 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	itoalen(long int n)
{
	int	count;

	count = 1;
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*nbr;
	int			neg;
	int			i;
	long int	nmb;

	neg = 0;
	nmb = n;
	if (nmb < 0)
	{
		neg = 1;
		nmb *= -1;
	}
	nbr = (char *)malloc(sizeof(char) * (itoalen(nmb) + neg + 1));
	if (!nbr)
		return (NULL);
	i = neg + itoalen(nmb) - 1;
	nbr[i + 1] = '\0';
	while (i >= 0 + neg)
	{
		nbr[i--] = nmb % 10 + 48;
		nmb = nmb / 10;
	}
	if (neg)
		nbr[0] = '-';
	return (nbr);
}
