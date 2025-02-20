/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:22:03 by andrean           #+#    #+#             */
/*   Updated: 2025/02/20 14:59:49 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//fonctions utilitaires pour la liste des mots (commandes, arguments, operateurs, etc...)

t_lst	*ft_lstlastword(t_lst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstback(t_lst **lst, t_lst *new)
{
	if (!new)
		return ;
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

int	assign_token(char *word, int ignoretoken)
{
	if (!ft_strncmp(word, "|", 2) && !ignoretoken)
		return (PIPE);
	if (!ft_strncmp(word, "<", 2) && !ignoretoken)
		return (INPUT);
	if (!ft_strncmp(word, ">", 2) && !ignoretoken)
		return (TRUNC);
	if (!ft_strncmp(word, ">>", 3) && !ignoretoken)
		return (APPEND);
	if (!ft_strncmp(word, "<<", 3) && !ignoretoken)
		return (HEREDOC);
	if (!ft_strncmp(word, "&&", 3) && !ignoretoken)
		return (AND);
	if (!ft_strncmp(word, "||", 2) && !ignoretoken)
		return (OR);
	return (0);
}

t_lst	*ft_lstnewword(char *word, int ignoretoken)
{
	t_lst	*node;

	if (!word)
		return (NULL);
	node = (t_lst *)malloc(sizeof(t_lst) * 1);
	if (!node)
		return (NULL);
	node->word = word;
	node->word_type = 0;
	node->prev = NULL;
	node->next = NULL;
	node->sub = NULL;
	node->word_type = assign_token(word, ignoretoken);
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
			ft_lstdeloneword(*lst);
			*lst = nxt;
		}
	}
}