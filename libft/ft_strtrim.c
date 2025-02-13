/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:19:35 by andrean           #+#    #+#             */
/*   Updated: 2024/11/19 10:12:14 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*findstart(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	trigger;

	i = 0;
	trigger = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				trigger = 1;
				break ;
			}
			j++;
		}
		if (trigger == 0)
			return ((char *)s1 + i);
		trigger = 0;
		i++;
	}
	return (0);
}

static int	findlen(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	trigger;

	i = ft_strlen(s1) - 1;
	trigger = 0;
	while (i >= 0)
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				trigger = 1;
				break ;
			}
			j++;
		}
		if (trigger == 0)
			return (i + 1);
		trigger = 0;
		i--;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	char	*start;
	int		len;

	start = findstart(s1, set);
	if (!start)
	{
		trim = (char *)malloc(sizeof(char) * 1);
		if (!trim)
			return (NULL);
		*trim = 0;
		return (trim);
	}
	len = findlen(start, set);
	trim = (char *)malloc(sizeof(char) * (len + 1));
	if (!trim)
		return (NULL);
	ft_memcpy(trim, start, len);
	trim[len] = '\0';
	return (trim);
}
