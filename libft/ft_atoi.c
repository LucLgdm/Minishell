/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 21:06:48 by andrean           #+#    #+#             */
/*   Updated: 2024/11/13 11:05:19 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long int	nbr;
	int			neg;

	nbr = 0;
	neg = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		neg *= -(*nptr - 44);
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = (nbr * 10) + *nptr - 48;
		nptr++;
	}
	return (nbr * neg);
}
