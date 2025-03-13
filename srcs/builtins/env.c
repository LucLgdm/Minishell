/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:18:07 by andrean           #+#    #+#             */
/*   Updated: 2025/03/13 17:40:01 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ast *node)
{
	(void)node;
	int			i;
	t_hashtable	*env;

	i = -1;
	env = (*get_world())->env;
	if (!env)
		env = (*get_world())->new_env;
	while (++i < env->length)
	{
		if (env->table[i])
			printf("%s=%s\n", env->table[i]->key, env->table[i]->value);
	}
	return (0);
}