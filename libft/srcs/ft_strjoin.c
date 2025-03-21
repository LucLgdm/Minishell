/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:36:50 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 11:56:19 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_size;
	size_t	s2_size;
	size_t	i;

	i = -1;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	str = (char *)malloc((s1_size + s2_size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (++i < s1_size)
		str[i] = s1[i];
	i = -1;
	while (++i < s2_size)
		str[s1_size + i] = s2[i];
	str[s1_size + i] = '\0';
	return (str);
}
