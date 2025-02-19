/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:26:58 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:33 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *s)
{
	char	*cpy;
	size_t	size_s;
	size_t	i;

	i = 0;
	size_s = ft_strlen(s);
	cpy = (char *)malloc((size_s + 1) * sizeof(char));
	if (!cpy)
		return (NULL);
	while (i < size_s)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
