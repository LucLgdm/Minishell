/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_hasht.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:33:57 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/14 15:31:45 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hashtable.h"

void	ft_free_hasht(t_hashtable *hasht)
{
	int	i;

	i = -1;
	if (hasht->table)
	{
		while (++i < hasht->length)
		{
			ft_free_element(&(hasht->table[i]));
		}
		free(hasht->table);
	}
	if (hasht)
		free(hasht);
}
