/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:00:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/17 14:57:29 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_handle_dollar(t_ast **node, t_hashtable *env)
{
	int		i;
	char	*expanded;
	char **splitted;

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
				free((*node)->cmd[i]);
				splitted = ft_split(expanded, ' ');
				(*node)->cmd = ft_catchartab((*node)->cmd, splitted, i);
				free(expanded);
			}
			else
				(*node)->cmd[i] = ft_strdup("");
		}
	}
}
