/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:35:41 by andrean           #+#    #+#             */
/*   Updated: 2025/04/04 11:58:58 by andrean          ###   ########.fr       */
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

static void	ft_fill_dir(char **dir)
{
	*dir = ft_calloc(255, 1);
	if (!(*dir))
		return ;
	*dir = getcwd(*dir, 255);
}

int	sub_file_exists(char *path, char *dir)
{
	DIR				*opened;
	struct dirent	*entry;

	if (!dir)
		return (-1);
	opened = opendir(dir);
	if (!opened)
		return (no_open(errno));
	if (!*path)
		return (free(dir), closedir(opened), 4);
	entry = readdir(opened);
	while (entry)
	{
		if (!ft_strcmp(entry->d_name, path))
			return (free(dir), closedir(opened), entry->d_type);
		entry = readdir(opened);
	}
	closedir(opened);
	free(dir);
	return (0);
}

int	file_exists(char *path_name)
{
	char			*dir;

	dir = NULL;
	if (ft_strcmp(path_name, "/") == 0)
		return (4);
	if (ft_strrchr(path_name, '/'))
	{
		dir = ft_substr(path_name, 0,
				ft_strrchr(path_name, '/') - path_name);
		path_name = ft_strrchr(path_name, '/') + 1;
	}
	else
		ft_fill_dir(&dir);
	return (sub_file_exists(path_name, dir));
}
