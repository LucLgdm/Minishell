/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:51:26 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:54:42 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temp;

	temp = lst;
	if (lst == NULL)
		return (NULL);
	while (temp->next)
		temp = temp->next;
	return (temp);
}
