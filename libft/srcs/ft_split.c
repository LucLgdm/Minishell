/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:23:21 by lde-merc          #+#    #+#             */
/*   Updated: 2024/11/27 13:55:27 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_countword(char *s, char c)
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
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

void	ft_calcul(char *s, char c, char **tab)
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
		while (s[i + size] != c && s[i + size])
			size++;
		tab[k] = (char *)malloc((size + 1) * sizeof(char));
		if (!tab[k])
			return ;
		ft_memcpy(tab[k], s + i, size);
		tab[k][size] = '\0';
		k++;
		i += size;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		n_word;

	if (s[0] == '\0')
	{
		tab = (char **)malloc(1 * sizeof(char *));
		if (!tab)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	n_word = ft_countword((char *)s, c);
	tab = (char **)malloc((n_word + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	ft_calcul((char *)s, c, tab);
	tab[n_word] = NULL;
	return (tab);
}
