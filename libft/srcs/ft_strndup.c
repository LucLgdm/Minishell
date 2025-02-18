/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:16:13 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:56:00 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*cpy;
	size_t	size_s;
	size_t	i;

	i = 0;
	size_s = ft_strlen(s);
	cpy = (char *)malloc((size_s + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (i < n)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
