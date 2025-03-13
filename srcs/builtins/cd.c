/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:34:49 by andrean           #+#    #+#             */
/*   Updated: 2025/03/13 15:59:41 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  /!\  ne pas creer de process avant d'appeler cette fonction, sinon inutile. 

int	ft_cd(t_ast *node)
{	
	t_hashtable	*env;

	env = get_world()->env;
	if (get_arg_nb(node) > 2)
		;//too many args
	if (get_arg_nb(node) == 1)
	{
		if (ft_get_element(env, "HOME"))
		{
			if (chdir(ft_get_element(env, "HOME")->value) == 0)
				;//change pwd && oldpwd
			else
				;//error
		}
		else
			;//"cd: HOME not set"
	}
	else
	{
		if (chdir(node->cmd[1]) == 0)
			;//change pwd && oldpwd
		else
			;//error
	}
	return (0);
}