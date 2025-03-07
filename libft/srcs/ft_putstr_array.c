/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:16:17 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/07 11:16:33 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putstr_array(char **str_array)
{
	int	index;

	index = 0;
	while (str_array[index])
	{
		ft_putstr_fd(str_array[index], 1);
		ft_putstr_fd(" ", 1);
		index++;
	}
	ft_putstr_fd("\n", 1);
}
