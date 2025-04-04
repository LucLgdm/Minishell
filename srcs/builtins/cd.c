/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:34:49 by andrean           #+#    #+#             */
/*   Updated: 2025/04/04 12:01:00 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  /!\  ne pas creer de process avant d'appeler cette fonction, sinon inutile. 

static int	cd_error(int error, char *directory)
{
	int	type;

	ft_putstr_fd("cd: ", 2);
	if (error == 0)
		ft_putstr_fd("too many arguments\n", 2);
	if (error == 1)
	{
		type = file_exists(directory);
		if (type == -1)
			return (-1);
		ft_putstr_fd(directory, 2);
		if (type == 0)
			ft_putstr_fd(": No such file or directory\n", 2);
		if (type == 4)
			ft_putstr_fd(": Permission denied\n", 2);
		if (type == 8)
			ft_putstr_fd(": Not a directory\n", 2);
	}
	if (error == 2)
		ft_putstr_fd("HOME not set\n", 2);
	return (1);
}

static void	change_wd(t_hashtable *env, char *pwd)
{
	char	newpwd[255];

	getcwd(newpwd, 255);
	if (ft_strcmp(pwd, newpwd))
	{
		if (ft_get_element(env, "OLDPWD"))
			ft_modify_value(env, "OLDPWD", pwd, 0);
		else
			ft_add_element(&env, "OLDPWD", pwd);
		if (ft_get_element(env, "PWD"))
			ft_modify_value(env, "PWD", newpwd, 0);
		else
			ft_add_element(&env, "PWD", newpwd);
	}
}

int	ft_cd(t_ast *node)
{	
	t_hashtable	*env;
	char		currentpwd[255];

	env = (*get_world())->env;
	if (!env)
		env = (*get_world())->new_env;
	getcwd(currentpwd, 255);
	if (get_arg_nb(node) > 2)
		return (cd_error(0, NULL));
	if (get_arg_nb(node) == 1)
	{
		if (ft_get_element(env, "HOME"))
		{
			if (chdir(ft_get_element(env, "HOME")->value) != 0)
				return (cd_error(1, ft_get_element(env, "HOME")->value));
		}
		else
			return (cd_error(2, NULL));
	}
	else if (ft_strcmp(node->cmd[1], "-") == 0)
		return (cd_error(1, node->cmd[1]));
	else if (chdir(node->cmd[1]) != 0)
		return (cd_error(1, node->cmd[1]));
	return (change_wd(env, currentpwd), 0);
}
