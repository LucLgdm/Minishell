/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:40:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/04 15:56:06 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hashtable.h"

t_hashtable	*ft_add_element(t_hashtable **htable, char *key, char *value)
{
	int			hash;
	t_element	*new_element;
	t_element	*current;

	hash = ft_hash(key, (*htable)->length);
	new_element = ft_create_element(key, value);
	if (!new_element)
		stop_when_calloc_fail();
	current = (*htable)->table[hash];
	if (!current)
		(*htable)->table[hash] = new_element;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new_element;
	}
	return ((*htable));
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
	if (!element->value)
		stop_when_calloc_fail();
	return (ht);
}

t_hashtable	*ft_remove_element(t_hashtable *htable, char *key)
{
	t_element	**tmp;
	t_element	**prev;
	int			index;
	t_element	*next;

	prev = NULL;
	index = ft_hash(key, htable->length);
	tmp = &(htable->table[index]);
	while (*tmp)
	{
		if (ft_strcmp((*tmp)->key, key) == 0)
		{
			next = (*tmp)->next;
			ft_free_element(tmp);
			if (prev)
				(*prev)->next = next;
			else
				htable->table[index] = next;
			break ;
		}
		prev = tmp;
		tmp = &((*tmp)->next);
	}
	return (htable);
}

void	ft_free_element(t_element **element)
{
	if (*element)
	{
		if ((*element)->key)
			free((*element)->key);
		if ((*element)->value)
			free((*element)->value);
		free(*element);
		*element = NULL;
	}
	return ;
}
