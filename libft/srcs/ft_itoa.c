/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 10:29:31 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:54:22 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_remplissage(char *str, int n, int i)
{
	if (n == -2147483648)
	{
		str[0] = '-';
		str[1] = '2';
		ft_remplissage(str, 147483648, i);
	}
	else if (n < 0)
	{
		n *= -1;
		str[0] = '-';
		ft_remplissage(str, n, i);
	}
	else if (n > 9)
	{
		ft_remplissage(str, n / 10, i - 1);
		ft_remplissage(str, n % 10, i);
	}
	else
	{
		str[i] = n + '0';
	}
}

char	*ft_itoa(int n)
{
	size_t	length;
	int		n2;
	char	*str;

	length = 0;
	n2 = n;
	while (n2)
	{
		n2 /= 10;
		length++;
	}
	if (n <= 0)
		length++;
	str = (char *)malloc((length + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_remplissage(str, n, length - 1);
	str[length] = '\0';
	return (str);
}
