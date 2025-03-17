/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:00:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/17 16:48:17 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_handle_dollar(t_ast **node, t_hashtable *env)
{
	int		i;
	char	*expanded;
	char	**splitted;
	char	**new_cmd;

	if (!node || !(*node) || !(*node)->cmd)
		return ;
	i = -1;
	while ((*node)->cmd[++i])
	{
		if (ft_strchr((*node)->cmd[i], '$'))
		{
			expanded = ft_expand((*node)->cmd[i], env);
			if (expanded)
			{
				splitted = ft_split(expanded, ' ');
				new_cmd = ft_catchartab((*node)->cmd, splitted, i);
				ft_free_array(splitted);
				ft_free_array((*node)->cmd);
				(*node)->cmd = new_cmd;
				free(expanded);
			}
			else
				(*node)->cmd[i] = ft_strdup("");
		}
	}
}
