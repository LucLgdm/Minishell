/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:52:30 by andrean           #+#    #+#             */
/*   Updated: 2024/11/18 11:56:57 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_ret(char c, int *ret)
{
	*ret += 1;
	write(1, &c, 1);
}

void	ft_putstrl(char *s, int *ret)
{
	int	len;

	if (!s)
	{
		ft_putstrl("(null)", ret);
		return ;
	}
	len = ft_strlen(s);
	write(1, s, len);
	*ret += len;
}

void	ft_putnbrl(int n, int *ret)
{
	if (n == -2147483648)
	{
		ft_putstrl("-2147483648", ret);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_ret('-', ret);
		n *= -1;
	}
	if (n > 9)
		ft_putnbrl(n / 10, ret);
	ft_putchar_ret((n % 10) + 48, ret);
}
