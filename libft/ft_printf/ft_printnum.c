/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:02:43 by andrean           #+#    #+#             */
/*   Updated: 2024/11/18 11:57:04 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_nbrprinter(long unsigned int nbr, char *base, int len, int *ret)
{
	if (nbr / len > 0)
		ft_nbrprinter(nbr / len, base, len, ret);
	ft_putchar_ret(base[nbr % len], ret);
}

void	ft_printhex(long unsigned int nbr, int islower, int *ret)
{
	char		*base;

	if (islower > 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (islower == 2)
		ft_nbrprinter(nbr, base, 16, ret);
	else
		ft_nbrprinter((unsigned int)nbr, base, 16, ret);
}

void	ft_printnum(unsigned int nbr, int *ret)
{
	ft_nbrprinter(nbr, "0123456789", 10, ret);
}

void	ft_printaddress(void *adress, int *ret)
{
	if (adress)
	{
		ft_putstrl("0x", ret);
		ft_printhex((long unsigned int)adress, 2, ret);
	}
	else
		ft_putstrl("(nil)", ret);
}
