/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:38:09 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:54 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*sortie;
	char	*str;
	size_t	i;
	size_t	s_size;

	str = (char *)s;
	i = -1;
	s_size = ft_strlen(str);
	sortie = (char *)malloc((s_size + 1) * sizeof(char));
	if (!sortie)
		return (NULL);
	while (++i < s_size)
		sortie[i] = f(i, str[i]);
	sortie[i] = '\0';
	return (sortie);
}
