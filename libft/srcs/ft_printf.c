/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:50:27 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:09 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_place(char c, va_list list, int *counter)
{
	if (c == 'c' || c == 's' || c == '%')
		ft_char(c, list, counter);
	else if (c == 'i' || c == 'd' || c == 'u')
		ft_number(c, list, counter);
	else if (c == 'x' || c == 'X')
		ft_number_hexa(c, list, counter);
	else if (c == 'p')
		ft_pointer(list, counter);
}

int	ft_printf(const char *s, ...)
{
	va_list	list;
	int		i;
	int		counter;

	counter = 0;
	if (!s)
		return (counter - 1);
	i = -1;
	va_start(list, s);
	while (s[++i])
	{
		if (s[i] == '%' && s[i + 1])
			ft_place(s[++i], list, &counter);
		else
		{
			ft_putchar_fd(s[i], 1);
			counter++;
		}
	}
	va_end(list);
	return (counter);
}
