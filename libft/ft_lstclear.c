/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:15:50 by andrean           #+#    #+#             */
/*   Updated: 2024/12/13 15:26:20 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nxt;

	if (lst)
	{
		while (*lst != NULL)
		{
			nxt = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = nxt;
		}
		free(lst);
	}
	lst = NULL;
}
