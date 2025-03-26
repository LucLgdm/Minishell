/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:59:40 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/26 12:36:32 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static long long	overflow(long long sign, char **endptr, char *str)
{
	errno = ERANGE;
	*endptr = (char *)&str;
	if (sign == 1)
		return (LLONG_MAX);
	return (LLONG_MIN);
}

long long	ft_strtoll(char *str, char **endptr, int base)
{
	long long	nbr;
	long long	sign;
	int			i;

	nbr = 0;
	sign = 1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (ft_isdigit(str[i]))
	{
		if ((nbr > LLONG_MAX / 10) || ((nbr == LLONG_MAX / 10)
				&& (ft_atoi(&str[i]) > LLONG_MAX % 10)))
			return (overflow(sign, endptr, &str[i]));
		nbr = nbr * base + str[i++] - '0';
	}
	*endptr = (char *)&str[i];
	return (sign * nbr);
}
