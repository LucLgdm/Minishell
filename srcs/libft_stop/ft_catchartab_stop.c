/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catchartab_stop.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:25:18 by andrean           #+#    #+#             */
/*   Updated: 2025/04/04 17:10:52 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**free_catchartab(char **tab1, char **tab2, char **tab3)
{
	if (tab1)
		ft_free_array(tab1);
	if (tab2)
		ft_free_array(tab2);
	if (tab3)
		ft_free_array(tab3);
	stop_when_calloc_fail();
	return (NULL);
}

char	**sub_catchartab(char **output, char **tab, int pos, int max)
{
	int	i;

	i = -1;
	while (++i < max)
	{
		output[i + pos] = ft_strdup(tab[i]);
		if (!output[i + pos])
			return (ft_free_array(output), NULL);
	}
	return (output);
}

char	**ft_catchartab_stop(char **tab1, char **tab2, int pos)
{
	int		n;
	int		m;
	char	**output;
	int		i;

	n = ft_arraylen(tab1);
	m = ft_arraylen(tab2);
	output = ft_calloc((n + m + 1), sizeof(char *));
	if (!output)
		return (free_catchartab(tab1, tab2, NULL));
	output = sub_catchartab(output, tab1, 0, pos);
	if (!output)
		return (free_catchartab(tab1, tab2, NULL));
	output = sub_catchartab(output, tab2, pos, m);
	if (!output)
		return (free_catchartab(tab1, tab2, NULL));
	i = pos + 1;
	while (i < n)
	{
		output[i + m - 1] = ft_strdup(tab1[i]);
		if (!output[i + m -1])
			return (free_catchartab(tab1, tab2, output));
		i++;
	}
	return (ft_free_array(tab1), ft_free_array(tab2), output);
}
