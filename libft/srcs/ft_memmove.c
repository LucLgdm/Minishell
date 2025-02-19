/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:32:15 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:03 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// La difference avec memcpy est qu'elle evite les chevauchements

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*destcpy;
	unsigned char	*srccpy;

	destcpy = (unsigned char *)dest;
	srccpy = (unsigned char *)src;
	if (destcpy == srccpy || n == 0)
		return (dest);
	if (destcpy < srccpy)
	{
		while (n--)
			*destcpy++ = *srccpy++;
	}
	else
	{
		destcpy += n;
		srccpy += n;
		while (n--)
			*(--destcpy) = *(--srccpy);
	}
	return (dest);
}
