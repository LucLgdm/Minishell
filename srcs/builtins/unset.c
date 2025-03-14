/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:26:53 by andrean           #+#    #+#             */
/*   Updated: 2025/03/14 14:18:22 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_ast *node)
{
	t_hashtable	*env;
	int			arg_nb;
	int			count;

	env = (*get_world())->env;
	if (!env)
		env = (*get_world())->new_env;
	arg_nb = get_arg_nb(node);
	count = 0;
	while (++count < arg_nb)
		ft_remove_element(env, node->cmd[count]);
	return (0);
}
