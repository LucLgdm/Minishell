/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:26:53 by andrean           #+#    #+#             */
/*   Updated: 2025/04/10 12:18:00 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_ast *node)
{
	t_hashtable	*env;
	t_hashtable	*hidden;
	int			arg_nb;
	int			count;

	hidden = (*get_world())->hidden_vars;
	env = (*get_world())->env;
	if (!env)
		env = (*get_world())->new_env;
	arg_nb = get_arg_nb(node);
	count = 0;
	while (++count < arg_nb)
	{
		env = ft_remove_element(env, node->cmd[count]);
		if (node->cmd[count][0] != '?')
			hidden = ft_remove_element(hidden, node->cmd[count]);
	}
	return (0);
}
