/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraycpy_stop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:29:25 by andrean           #+#    #+#             */
/*   Updated: 2025/03/26 11:13:09 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arraycpy_stop(char **tab)
{
	char	**cpy;
	int		len;
	int		i;

	i = -1;
	len = ft_arraylen(tab);
	cpy = (char **)ft_calloc_stop(sizeof(char *), len + 1);
	while (tab[++i])
		cpy[i] = ft_strdup_stop(tab[i]);
	return (cpy);
}
