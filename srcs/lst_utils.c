/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:22:03 by andrean           #+#    #+#             */
/*   Updated: 2025/02/13 12:30:06 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//fonctions utilitaires pour la liste des mots (commandes, arguments, operateurs, etc...)

void	ft_lstback(t_lst **lst, t_lst *new)
{
	if (lst)
	{
		while (*lst != NULL)
		{
			new->prev = *lst;
			lst = &((*lst)->next);
		}
		*lst = new;
	}
}

t_lst	*ft_lstnewword(char *word)
{
	t_lst	*node;

	node = (t_lst *)malloc(sizeof(t_lst) * 1);
	if (!node)
		return (NULL);
	node->word = word;
	node->word_type = 0;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	ft_lstdeloneword(t_lst *lst)
{
	if (lst)
	{
		free(lst->word);
		free(lst);
	}
}

void	ft_lstclearwords(t_lst **lst)
{
	t_lst	*nxt;

	if (lst)
	{
		while (*lst != NULL)
		{
			nxt = (*lst)->next;
			ft_lstdelone(*lst);
			*lst = nxt;
		}
		free(lst);
	}
}