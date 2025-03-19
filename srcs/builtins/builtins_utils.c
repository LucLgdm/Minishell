/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:35:41 by andrean           #+#    #+#             */
/*   Updated: 2025/03/19 17:21:07 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_open(int err)
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

int	file_exists(char *path_name)
{
	char	*dir;
	DIR		*opened;
	struct dirent	*entry;

	if (ft_strrchr(path_name, '/'))
	{
		dir = ft_substr(path_name, 0, ft_strrchr(path_name, '/') - path_name);
		path_name = ft_strrchr(path_name, '/') + 1;
	}
	else
	{
		dir = ft_calloc(255, 1);
		dir = getcwd(dir, 255);
	}
	opened = opendir(dir);
	if (!opened)
		return (no_open(errno));
	if (!*path_name)
	{
		free(dir);
		closedir(opened);
		return (4);
	}
	entry = readdir(opened);
	while (entry)
	{
		if (!ft_strcmp(entry->d_name, path_name))
		{
			free(dir);
			closedir(opened);
			return (entry->d_type);
		}
		entry = readdir(opened);
	}
	closedir(opened);
	free(dir);
	return (0);
}