/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:40:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/12 15:45:43 by lde-merc         ###   ########.fr       */
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


t_hashtable	*ft_modify_value(t_hashtable *ht, char *key, char *value, int add)
{
	t_element	*element;
	char		*value_tmp;
	
	element = ft_get_element(ht, key);
	if (!element)
		return (ht);
	value_tmp = element->value;
	if (add)
		element->value = ft_strjoin(element->value, value);
	else
		element->value = ft_strdup(value);
	free(value_tmp);
	return (ht);
}


t_hashtable	*ft_remove_element(t_hashtable *htable, char *key)
{
	int			hash;
	t_element	**tmp_table;
	
	hash = ft_hash(key, htable->length);
	tmp_table = htable->table;
	while(tmp_table[hash])
	{
		if (ft_strcmp(tmp_table[hash]->key, key))
		{
			ft_free_element(tmp_table[hash]);
			tmp_table[hash] = NULL;
		}
		hash = (hash + 1) % htable->length;
	}
	return (htable);
}

void	ft_free_element(t_element *element)
{
	if (element)
	{
		if (element->key)
			free(element->key);
		if (element->value)
			free(element->value);
		free(element);
	}
	return ;
}
