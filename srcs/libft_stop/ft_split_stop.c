/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_stop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:23:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/04 15:17:08 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_skip_quotes(char *str, size_t *size, char quote)
{
	(*size)++;
	while (str[*size] && str[*size] != quote)
	{
		(*size)++;
	}
}

static int	ft_countword(char *s, char c)
{
	size_t	i;
	int		count;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		if (s[i] == '\'' || s[i] == '"')
		{
			ft_skip_quotes(s, &i, s[i]);
		}
		if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	**ft_calcul(char *s, char c, char ***tab, int i)
{
	int		k;
	size_t	size;

	k = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		size = 0;
		if (s[i] == '\'' || s[i] == '"')
			ft_skip_quotes(s, &size, s[i]);
		while (s[i + size] != c && s[i + size])
			size++;
		(*tab)[k] = (char *)ft_calloc((size + 1), sizeof(char));
		if (!(*tab)[k])
			return (ft_free_array((*tab)), (*tab) = NULL);
		ft_memcpy((*tab)[k], s + i, size);
		(*tab)[k][size] = '\0';
		k++;
		i += size;
	}
	return (NULL);
}

char	**ft_split_stop(char const *s, char c, int free_s)
{
	char	**tab;
	int		n_word;

	if (s[0] == '\0')
	{
		tab = (char **)ft_calloc(1, sizeof(char *));
		if (!tab && free_s)
			return (free((char *)s), NULL);
		else if (!tab)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	n_word = ft_countword((char *)s, c);
	tab = (char **)ft_calloc((n_word + 1), sizeof(char *));
	if (!tab && free_s)
		return (free((char *)s), NULL);
	else if (!tab)
		return (NULL);
	ft_calcul((char *)s, c, &tab, 0);
	if (free_s)
		free((char *)s);
	if (!tab)
		stop_when_calloc_fail();
	return (tab);
}
