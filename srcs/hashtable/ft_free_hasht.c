/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_hasht.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:33:57 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 18:35:14 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/hashtable.h"

void	ft_free_hasht(t_hashtable *hasht)
{
	t_element	*next;
	t_element	*tmp;
	int			i;

	i = -1;
	if (hasht->table)
	{
		while (++i < hasht->length)
		{
			tmp = hasht->table[i];
			while (tmp)
			{
				next = tmp->next;
				ft_free_element(&(tmp));
				tmp = next;
			}
		}
		free(hasht->table);
	}
	if (hasht)
		free(hasht);
}
