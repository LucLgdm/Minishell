/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:36:50 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:39 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_size;
	size_t	s2_size;
	size_t	i;

	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	str = (char *)malloc((s1_size + s2_size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < s1_size)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_size)
	{
		str[s1_size + i] = s2[i];
		i++;
	}
	str[s1_size + i] = '\0';
	return (str);
}
