/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_stop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:56:06 by andrean           #+#    #+#             */
/*   Updated: 2025/03/21 16:56:53 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_remplissage(char *str, int n, int i)
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

char	*ft_itoa_stop(int n)
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
	str = (char *)ft_calloc_stop((length + 1), sizeof(char));
	if (!str)
		return (NULL);
	ft_remplissage(str, n, length - 1);
	str[length] = '\0';
	return (str);
}