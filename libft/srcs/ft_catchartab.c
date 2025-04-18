/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catchartab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:16:41 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 16:06:55 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_catchartab(char **tab1, char **tab2, int pos)
{
	int		n;
	int		m;
	char	**output;
	int		i;

	n = ft_arraylen(tab1);
	m = ft_arraylen(tab2);
	output = ft_calloc((n + m + 1), sizeof(char *));
	if (!output)
		return (NULL);
	i = -1;
	while (++i < pos)
		output[i] = ft_strdup(tab1[i]);
	i = -1;
	while (++i < m)
		output[pos + i] = ft_strdup(tab2[i]);
	i = pos + 1;
	while (i < n)
	{
		output[i + m - 1] = ft_strdup(tab1[i]);
		i++;
	}
	ft_free_array(tab1);
	ft_free_array(tab2);
	return (output);
}
