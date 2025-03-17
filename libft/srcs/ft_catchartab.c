/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catchartab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:16:41 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/17 14:27:14 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**ft_catchartab(char **tab1, char **tab2, int pos)
{
	int		n;
	int		m;
	char	**output;
	int		i;
	int		j;

	n = ft_arraylen(tab1);
	m = ft_arraylen(tab2);
	output = malloc((n + m + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	i = -1;
	while (++i < pos)
		output[i] = ft_strdup(tab1[i]);
	j = -1;
	while (++j < m)
		output[pos + j] = ft_strdup(tab2[j]);
	i = pos + m - 1;
	while (++i < n + m)
		output[i] = ft_strdup(tab1[i - m]);
	output[n + m] = NULL;
	ft_free_array(tab1);
	ft_free_array(tab2);
	return (output);
}
