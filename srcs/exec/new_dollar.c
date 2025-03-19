/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:00:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/19 17:25:06 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_handle_dollar(char ***cmd, t_hashtable *env)
{
	int		i;
	char	*expanded;
	char	**splitted;
	char	**new_cmd;

	if (!*cmd)
		return ;
	i = -1;
	while ((*cmd)[++i])
	{
		if (ft_strchr((*cmd)[i], '$'))
		{
			expanded = ft_expand((*cmd)[i], env);
			if (expanded)
			{
				splitted = ft_split(expanded, ' ');
				new_cmd = ft_catchartab(*cmd, splitted, i);
				ft_free_array(splitted);
				ft_free_array(*cmd);
				*cmd = new_cmd;
				free(expanded);
			}
			else
				(*cmd)[i] = ft_strdup("");
		}
		(*cmd) = manage_quotes(*cmd, (*cmd)[i], i);
	}
}
