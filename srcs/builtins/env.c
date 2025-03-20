/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:18:07 by andrean           #+#    #+#             */
/*   Updated: 2025/03/20 16:55:06 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_ast *node)
{
	int			i;
	t_hashtable	*env;
	t_element	*tmp;

	usleep(5000000);
	(void)node;
	i = -1;
	env = (*get_world())->env;
	if (!env)
		env = (*get_world())->new_env;
	while (++i < env->length)
	{
		tmp = env->table[i];
		while (tmp)
		{
			ft_printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	return (0);
}
