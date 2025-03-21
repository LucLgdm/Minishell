/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:02:04 by andrean           #+#    #+#             */
/*   Updated: 2025/03/21 17:17:55 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	checkifwildcarded(char **trunclst, char *name)
{
	int	i;

	i = -1;
	if (name && name[0] == '.')
		if (ft_strncmp(trunclst[0], ".", 1))
			return (0);
	if (ft_strcmp(trunclst[0], "*"))
		if (ft_strncmp(name, trunclst[0], ft_strlen(trunclst[0])))
			return (0);
	while (trunclst[++i])
	{
		if (ft_strcmp(trunclst[i], "*"))
		{
			name = ft_strnstr(name, trunclst[i], 256);
			if (!name)
				return (0);
			name += ft_strlen(trunclst[i]);
		}
	}
	if (ft_strcmp(trunclst[i - 1], "*") && (ft_strlen(name) && !foundlast(name,
				trunclst[i - 1])))
		return (0);
	return (1);
}

char	**expand_lst(char **trunclst)
{
	DIR				*dir;
	char			wd[250];
	struct dirent	*entry;
	char			**lst;

	lst = ft_calloc_stop(sizeof(char *), 1);
	dir = opendir(getcwd(wd, 250));
	if (!dir)
		perror("");
	entry = readdir(dir);
	while (entry)
	{
		if (checkifwildcarded(trunclst, entry->d_name))
			lst = ft_catchartab_stop(lst, onelinetab(entry->d_name),
					ft_arraylen(lst));
		entry = readdir(dir);
	}
	if (!lst[0])
	{
		ft_free_array(lst);
		lst = NULL;
	}
	closedir(dir);
	return (lst);
}

char	**manage_wildcards(char **args, int index, char **trunclst)
{
	char	**new_args;

	if (!trunclst)
		return (args);
	new_args = expand_lst(trunclst);
	if (!new_args || !(*new_args))
		return (args);
	new_args = ft_catchartab_stop(args, new_args, index);
	return (new_args);
}
