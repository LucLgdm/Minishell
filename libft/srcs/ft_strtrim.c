/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:04:53 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:56:13 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <string.h>

int	ft_isin(char c, char *set)
{
	int	i;

	i = -1;
	while (set[++i])
	{
		if (set[i] == c)
			return (1);
	}
	return (0);
}

size_t	ft_calc(char const *s1, char *set2)
{
	char	*str;
	size_t	length;
	size_t	i;

	str = (char *)s1;
	length = ft_strlen(str);
	i = -1;
	while (ft_isin(str[ft_strlen(str) - 1 - ++i], set2) == 1)
		length--;
	if (length == 0)
		return (0);
	i = -1;
	while (ft_isin(str[++i], set2) == 1)
		length--;
	return (length);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	size;
	size_t	i;
	size_t	j;

	if (((char *)set)[0] == '\0')
	{
		str = ft_strdup(s1);
		return (str);
	}
	size = ft_calc(s1, (char *)set);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (ft_isin((char)s1[i], (char *)set) == 1)
		i++;
	j = -1;
	while (++j < size)
		str[j] = s1[i + j];
	str[j] = '\0';
	return (str);
}
