/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:19:46 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/04 17:21:51 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

bool	ft_isprime(int n)
{
	int	i;

	if (n == 2)
		return (true);
	if (n <= 1 || n % 2 == 0)
		return (false);
	i = 3;
	while (i <= n / i)
	{
		if (n % i == 0)
			return (false);
		i += 2;
	}
	return (true);
}
