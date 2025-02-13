/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:17:18 by andrean           #+#    #+#             */
/*   Updated: 2024/11/19 10:11:29 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	clean(char **s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (0);
}

static int	countwords(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**subsplit(char const *s, char c, char **split, int wordcount)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i] && k < wordcount)
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[j] != c && s[j] != 0)
			j++;
		split[k] = ft_substr(s, i, j - i);
		if (!split[k])
		{
			clean(split);
			return (NULL);
		}
		i = j;
		k++;
	}
	split[k] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	int		wordcount;
	char	**split;

	wordcount = countwords(s, c);
	split = (char **)malloc(sizeof(char *) * (wordcount + 1));
	if (!split)
		return (NULL);
	return (subsplit(s, c, split, wordcount));
}
