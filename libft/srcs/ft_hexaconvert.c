/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexaconvert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:06:18 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:54:03 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_number_hexa(char c, va_list list, int *counter)
{
	unsigned int	nbr;
	char			*base;

	nbr = va_arg(list, unsigned int);
	if (c == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	ft_putnbr_hexa(nbr, base, counter);
}

void	ft_putnbr_hexa(unsigned long n, char *base, int *counter)
{
	if (n >= 16)
		ft_putnbr_hexa(n / 16, base, counter);
	ft_putchar_fd(base[n % 16], 1);
	(*counter)++;
}
