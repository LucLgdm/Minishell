/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:44:27 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:54:00 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*exit;

	if (size && (nmemb > SIZE_MAX / size))
		return (NULL);
	exit = (void *)malloc(nmemb * size);
	if (!exit)
		return (NULL);
	ft_bzero(exit, nmemb * size);
	return (exit);
}
