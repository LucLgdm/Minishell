/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:41:20 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:22 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	s_size;
	size_t	i;

	s_size = ft_strlen(s);
	i = -1;
	while (++i < s_size)
		ft_putchar_fd(s[i], fd);
}
