/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:05:07 by andrean           #+#    #+#             */
/*   Updated: 2025/03/12 17:28:47 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_ast *node)
{
	int			exit_value;
	t_hashtable	*env;

	exit_value = ft_atoi(ft_get_element(env, "?"));
	if (get_arg_nb(node) > 1)
		exit_value = ft_atoi(node->cmd[1]);
	free_all(get_world());
	printf("\033[0;32mFrom Minishell with Love !\033[0m\n");
	exit(exit_value);
}