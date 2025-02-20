/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:55:44 by andrean           #+#    #+#             */
/*   Updated: 2025/02/20 16:14:34 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_tab(t_lst *words)
{
	char	**tab;
	t_lst	*start;
	int		count;
	int		i;

	count = 0;
	i = -1;
	if (words->word_type != 0)
		return (NULL);
	start = words;
	while (words && words->word_type == 0)
	{
		count++;
		words = words->next;
	}
	tab = ft_calloc(sizeof(char *), count + 1);
	while (++i < count)
	{
		tab[i] = start->word;
		start = start->next;
	}
	return (tab);
}

char	**path_tab(void)
{
	char	*path;
	char	*tmp;
	char	**tab;
	int		i;

	i = -1;
	path = getenv("PATH");
	if (!path)
		return (NULL);
	tab = ft_split(path, ':');
	while (tab[++i])
	{
		tmp = ft_strjoin(tab[i], "/");
		free(tab[i]);
		tab[i] = tmp;
	}
}

char	**getenvp(void)
{
	static char	**envp;

	return (envp);
}