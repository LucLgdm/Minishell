/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_creation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:35:36 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/28 13:05:16 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashtable.h"

t_hashtable	*ft_create_hashtable(int length)
{
	t_hashtable	*new_hashtable;
	int			i;

	new_hashtable = (t_hashtable *)ft_calloc_stop(sizeof(t_hashtable), 1);
	if (!new_hashtable)
		return (NULL);
	new_hashtable->length = length;
	new_hashtable->table = (t_element **)ft_calloc_stop(sizeof(t_element *),
			length);
	if (!new_hashtable->table)
	{
		free(new_hashtable);
		return (NULL);
	}
	i = -1;
	while (++i < length)
		new_hashtable->table[i] = NULL;
	return (new_hashtable);
}

t_element	*ft_create_element(char *key, char *value)
{
	t_element	*new_element;

	new_element = (t_element *)ft_calloc(sizeof(t_element), 1);
	if (!new_element)
		return (NULL);
	new_element->key = ft_strdup(key);
	if (!new_element->key)
		return (free(new_element), NULL);
	new_element->value = ft_strdup(value);
	if (!new_element->value)
		return (free(new_element), free(key), NULL);
	new_element->next = NULL;
	return (new_element);
}

int	ft_hash(char *key, int length)
{
	int	i;
	int	result;
	int	goat_number;

	i = -1;
	result = 0;
	goat_number = 89;
	while (key[++i])
		result += goat_number * (int)key[i] * i;
	return (result % length);
}
