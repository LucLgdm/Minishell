/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_stop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:23:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 16:57:14 by andrean          ###   ########.fr       */
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

static void	ft_calcul(char *s, char c, char **tab)
{
	int		i;
	int		k;
	size_t	size;

	i = 0;
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
		tab[k] = (char *)ft_calloc_stop((size + 1), sizeof(char));
		if (!tab[k])
			return ;
		ft_memcpy(tab[k], s + i, size);
		tab[k][size] = '\0';
		k++;
		i += size;
	}
}

char	**ft_split_stop(char const *s, char c)
{
	char	**tab;
	int		n_word;

	if (s[0] == '\0')
	{
		tab = (char **)ft_calloc_stop(1, sizeof(char *));
		if (!tab)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	n_word = ft_countword((char *)s, c);
	tab = (char **)ft_calloc_stop((n_word + 1), sizeof(char *));
	if (!tab)
		return (NULL);
	ft_calcul((char *)s, c, tab);
	tab[n_word] = NULL;
	return (tab);
}
