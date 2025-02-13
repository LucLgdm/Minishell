/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:38:57 by andrean           #+#    #+#             */
/*   Updated: 2024/12/03 17:05:44 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*map;
	t_list	*start;

	if (!lst)
		return (NULL);
	map = ft_lstnew((*f)(lst->content));
	if (!map)
		return (NULL);
	start = map;
	while (lst->next)
	{
		lst = lst->next;
		map->next = ft_lstnew((*f)(lst->content));
		if (!(map->next))
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		map = map->next;
	}
	return (start);
}
