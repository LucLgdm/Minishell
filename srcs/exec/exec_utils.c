/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:24:49 by andrean           #+#    #+#             */
/*   Updated: 2025/03/10 11:26:30 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**path_tab(t_hashtable hashtable)
{
	char	*path;
	char	*tmp;
	char	**tab;
	int		i;

	i = -1;
	path = ft_get_element(&hashtable, "PATH")->value;
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
