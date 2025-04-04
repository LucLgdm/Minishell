/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraycpy_stop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:29:25 by andrean           #+#    #+#             */
/*   Updated: 2025/04/04 10:19:24 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arraycpy(char **tab)
{
	char	**cpy;
	int		len;
	int		i;

	i = -1;
	len = ft_arraylen(tab);
	cpy = (char **)ft_calloc(sizeof(char *), len + 1);
	if (!cpy)
		return (NULL);
	while (tab[++i])
	{
		cpy[i] = ft_strdup(tab[i]);
		if (!cpy[i])
			return (ft_free_array(cpy), NULL);
	}
	return (cpy);
}
