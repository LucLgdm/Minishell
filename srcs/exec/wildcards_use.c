/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_use.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:37:57 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 17:07:12 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**onewildtab(void)
{
	char	**tab;

	tab = ft_calloc_stop(sizeof(char *), 2);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup_stop("*");
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

char	**onelinetab(char *str)
{
	char	**tab;
	if (!str)
		return (NULL);
	tab = ft_calloc_stop(sizeof(char *), 2);
	tab[0] = ft_strdup_stop(str);
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}

	return (tab);
}

int	foundlast(char *name, char *trunc)
{
	int	i;

	i = ft_strlen(name) - ft_strlen(trunc);
	if (i < 0)
		return (0);
	if (ft_strcmp(name + i, trunc))
		return (0);
	return (1);
}
