/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:02:04 by andrean           #+#    #+#             */
/*   Updated: 2025/03/18 15:53:54 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**onewildtab(void)
{
	char	**tab;

	tab = ft_calloc(sizeof(char *), 2);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup("*");
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

char	**onelinetab(char *str)
{
	char	**tab;

	if (!str)
		return (NULL);
	tab = ft_calloc(sizeof(char *), 2);
	tab[0] = ft_strdup(str);
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

int	foundlast(char *name, char *trunc)
{
	int	i;

	i = ft_strlen(name) - ft_strlen(trunc);
	if (i < 0)
		return (0);
	if (ft_strcmp(name + i, trunc))
		return (0);
	return (1);
}

int	checkifwildcarded(char **trunclst, char *name)
{
	int		i;
	i = -1;
	
	if (name && name[0] == '.')
		if (ft_strncmp(trunclst[0], ".", 1))
			return (0);
	if (ft_strcmp(trunclst[0], "*"))
		if (ft_strncmp(name, trunclst[0], ft_strlen(trunclst[0])))
			return(0);
	while (trunclst[++i])
	{
		if(ft_strcmp(trunclst[i], "*"))
		{
			name = ft_strnstr(name, trunclst[i], 256);
			if (!name)
				return(0);
			name += ft_strlen(trunclst[i]);
		}
	}
	if (ft_strcmp(trunclst[i - 1], "*") && (ft_strlen(name) && !foundlast(name, trunclst[i - 1])))
		return (0);
	return (1);
}

char	**expand_lst(char **trunclst)
{
	DIR				*dir;
	char			wd[250];
	struct dirent	*entry;
	char			**lst;

	lst = ft_calloc(sizeof(char *), 1);
	dir = opendir(getcwd(wd, 250));
	if (!dir)
		;//error
	entry = readdir(dir);
	while (entry)
	{
		if (checkifwildcarded(trunclst, entry->d_name))
			lst = ft_catchartab(lst, onelinetab(entry->d_name), ft_arraylen(lst));
		entry = readdir(dir);
	}
	if (!lst[0])
	closedir(dir);
	return (lst);
}

char	**manage_wildcards(char **args, int	index, char **trunclst)
{
	char	**new_args;

	if (!trunclst)
		return (args);
	new_args = expand_lst(trunclst);
	if (!new_args || !*new_args)
		return (args);
	new_args = ft_catchartab(args, new_args, index);
	ft_free_array(args);
	return (new_args);
}

// int	main(int ac, char **av)
// {
// 	char	**words;
// 	int		i;

// 	i = -1;
// 	words = ft_calloc(sizeof(char *), 1);
// 	while (++i < ac)
// 		words = ft_catchartab(words, onelinetab(av[i]), ft_arraylen(words));
// 	i = -1;
// 	while (++i < ac)
// 		words = manage_wildcards(words, words[i], i);
// 	i = -1;
// 	while (words[++i])
// 		printf("%s\n", words[i]);
// 	return (0);
// }