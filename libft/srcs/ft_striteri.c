/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:10:43 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:36 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	s_size;

	if (!s || !f)
		return ;
	s_size = ft_strlen(s);
	while (s_size--)
		f(s_size, &s[s_size]);
}
