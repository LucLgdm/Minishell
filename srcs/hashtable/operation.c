/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:40:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/05 14:52:53 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashtable.h"

t_hashtable	*ft_add_element(t_hashtable *htable, char *key, char *value)
{
	int			hash;
	t_element	*new_element;
	t_element	*current;

	hash = ft_hash(key, htable->length);
	new_element = ft_create_element(key, value);
	if (!new_element)
		return (NULL);
	if (!htable->table[hash])
		htable->table[hash] = new_element;
	else
	{
		current = htable->table[hash];
		while (current->next)
			current = current->next;
		current->next = new_element;
	}
	return (htable);
}

t_element	*ft_get_element(t_hashtable *htable, char *key)
{
	int			index;
	t_element	*current;

	index = ft_hash(key, htable->length);
	current = htable->table[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}
