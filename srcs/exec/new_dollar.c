/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:00:21 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 11:51:30 by lde-merc         ###   ########.fr       */
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
				free(expanded);
				*cmd = new_cmd;
			}
			else
				(*cmd)[i] = ft_strdup("");
		}
		(*cmd) = manage_quotes(*cmd, (*cmd)[i], i);
	}
}
