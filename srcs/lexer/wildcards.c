/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:02:04 by andrean           #+#    #+#             */
/*   Updated: 2025/03/17 15:50:28 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**onewildtab(void)
{
	char	**tab;

	tab = ft_calloc(sizeof(char *), 2);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup("*");
	if (tab[0])
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
	tab[0] = str;
	return (tab);
}

char	**get_trnclst(char *str)
{
	char	**trunclst;
	char	*wild;

	trunclst = ft_calloc(sizeof(char *), 1);
	wild = ft_strchr(str, '*');
	if (!wild)
		return (NULL);
	while (wild)
	{
		if (wild != str)
		{
			trunclst = ft_catchartab(trunclst, onelinetab(
						ft_substr(str, 0, wild - str)), ft_arraylen(trunclst));
			trunclst = ft_catchartab(trunclst,
					onewildtab(), ft_arraylen(trunclst));
		}
		else
			trunclst = ft_catchartab(trunclst,
					onewildtab(), ft_arraylen(trunclst));
		str = wild + 1;
		wild = ft_strchr(str, '*');
	}
	if (*str)
		trunclst = ft_catchartab(trunclst, onelinetab(
					ft_strdup(str)), ft_arraylen(trunclst));
	return (trunclst);
}

int	checkifwildcarded(char **trunclst, char *name)
{
	int		i;
	i = -1;
	
	if (ft_strcmp(trunclst[0], "*"))
		if (ft_strncmp(name, trunclst[0], ft_strlen(trunclst[0])))
			return(0);
	while (trunclst[++i])
	{
		if(ft_strcmp(trunclst[i], "*"))
		{
			if (!ft_strnstr(name, trunclst[i], 256))
				return(0);
			name += ft_strlen(trunclst[i]);
		}
	}
	if (ft_strcmp(trunclst[i - 1], "*") && ft_strlen(name))
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
}

char	**manage_wildcards(char **args, char *str, int	index)
{
	char	**new_args;
	char	**trunclst;

	trunclst = get_trnclst(str);
	if (!trunclst)
		return (args);
	new_args = expand_lst(trunclst);
	new_args = ft_catchartab(args, new_args, index);
	return (new_args);
}

int	main(int ac, char **av)
{
	char	**words;
	int		i;

	i = -1;
	words = ft_calloc(sizeof(char *), 1);
	while (++i < ac)
		words = ft_catchartab(words, av[i], ft_arraylen(words));
	i = -1;
	while (++i < ac)
		printf("%s\n", words[i]);
	return (0);
}