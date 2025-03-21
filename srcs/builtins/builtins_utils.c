/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:35:41 by andrean           #+#    #+#             */
/*   Updated: 2025/03/21 17:09:38 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_open(int err)
{
	if (err == 13)
		return (4);
	if (err == 2)
		return (0);
	printf("new_errno\n");
	return (-1);
}

int	get_arg_nb(t_ast *node)
{
	int	i;

	i = 0;
	if (node->cmd)
	{
		while (node->cmd[i])
			i++;
	}
	return (i);
}

static void	ft_fill_dir(char *dir)
{
	dir = ft_calloc_stop(255, 1);
	dir = getcwd(dir, 255);
}

int	file_exists(char *path_name)
{
	char			*dir;
	DIR				*opened;
	struct dirent	*entry;

	dir = NULL;
	if (ft_strrchr(path_name, '/'))
	{
		dir = ft_substr_stop(path_name, 0, ft_strrchr(path_name, '/') - path_name);
		path_name = ft_strrchr(path_name, '/') + 1;
	}
	else
		ft_fill_dir(dir);
	opened = opendir(dir);
	if (!opened)
		return (no_open(errno));
	if (!*path_name)
		return (free(dir), closedir(opened), 4);
	entry = readdir(opened);
	while (entry)
	{
		if (!ft_strcmp(entry->d_name, path_name))
			return (free(dir), closedir(opened), entry->d_type);
		entry = readdir(opened);
	}
	return (closedir(opened), free(dir), 0);
}
