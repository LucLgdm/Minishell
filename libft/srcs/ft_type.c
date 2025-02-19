/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 09:09:25 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:56:31 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_char(char c, va_list list, int *counter)
{
	char	*temp;

	temp = NULL;
	if (c == 'c')
	{
		ft_putchar_fd((char)va_arg(list, int), 1);
		(*counter)++;
	}
	else if (c == 's')
	{
		temp = (va_arg(list, char *));
		if (!temp)
		{
			ft_putstr_fd("(null)", 1);
			(*counter) += 6;
			return ;
		}
		ft_putstr_fd(temp, 1);
		(*counter) += ft_strlen(temp);
	}
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		(*counter)++;
	}
}

void	ft_number(char c, va_list list, int *counter)
{
	int				nbr;
	unsigned int	unbr;

	if (c == 'u')
	{
		unbr = va_arg(list, unsigned int);
		ft_unsigned_number(unbr);
		*counter += ft_unsigned_len(unbr);
	}
	else if (c == 'd' || c == 'i')
	{
		nbr = va_arg(list, int);
		if (nbr == -2147483648)
		{
			ft_putstr_fd("-2147483648", 1);
			*counter += 11;
		}
		else
		{
			ft_putnbr_fd(nbr, 1);
			*counter += ft_signed_len(nbr);
		}
	}
}

void	ft_pointer(va_list list, int *counter)
{
	void			*ptr;
	unsigned long	addr;
	char			*base;

	base = "0123456789abcdef";
	ptr = va_arg(list, void *);
	if (ptr == NULL)
	{
		ft_putstr_fd("(nil)", 1);
		*counter += 5;
	}
	else
	{
		addr = (unsigned long)ptr;
		ft_putstr_fd("0x", 1);
		*counter += 2;
		ft_putnbr_hexa(addr, base, counter);
	}
}
