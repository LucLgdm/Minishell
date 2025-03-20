/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:18:07 by andrean           #+#    #+#             */
/*   Updated: 2025/03/20 09:22:58 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ast *node)
{
	int			i;
	t_hashtable	*env;

	(void)node;
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
