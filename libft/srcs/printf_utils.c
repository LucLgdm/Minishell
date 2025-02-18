/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:24:09 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:56:39 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_unsigned_number(unsigned int nbr)
{
	if (nbr >= 10)
		ft_unsigned_number(nbr / 10);
	ft_putchar_fd((nbr % 10) + '0', 1);
}

int	ft_unsigned_len(unsigned int nbr)
{
	int	res;

	res = 0;
	while (nbr > 9)
	{
		nbr /= 10;
		res++;
	}
	if (nbr < 10)
		res++;
	return (res);
}

int	ft_signed_len(int nbr)
{
	int	res;

	res = 0;
	if (nbr < 0)
	{
		res++;
		nbr *= -1;
	}
	while (nbr > 9)
	{
		nbr /= 10;
		res++;
	}
	if (nbr < 10)
		res++;
	return (res);
}
