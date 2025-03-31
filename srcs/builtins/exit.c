/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:05:07 by andrean           #+#    #+#             */
/*   Updated: 2025/03/27 15:55:31 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_exit(t_ast *node)
// {
// 	int			exit_value;
// 	t_hashtable	*env;

// 	env = (*get_world())->hidden_vars;
// 	exit_value = ft_atoi(ft_get_element(env, "?")->value);
// 	if (get_arg_nb(node) > 1)
// 		exit_value = ft_atoi(node->cmd[1]);
// 	free_all(*get_world());
// 	printf("\033[0;32mFrom Minishell with Love !\033[0m\n");
// 	exit(exit_value);
// }

void	ft_exit(t_ast *node)
{
	long long	exit_value;
	t_hashtable	*env;

	env = (*get_world())->hidden_vars;
	exit_value = ft_atoi(ft_get_element(env, "?")->value);
	if (get_arg_nb(node) > 1)
		exit_value = exit_long(node, &exit_value);
	if (get_arg_nb(node) > 2)
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		return ;
	}
	free_all(get_world());
	if (*is_in_process())
		printf("\033[0;32mexit\nFrom Minishell with Love !\033[0m\n");
	exit(exit_value);
}

long long	exit_long(t_ast *node, long long *exit_value)
{
	char	*endptr;
	char	*arg;

	arg = node->cmd[1];
	errno = 0;
	*exit_value = ft_strtoll(arg, &endptr, 10);
	if (*endptr != '\0' || errno == ERANGE)
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", arg);
		*exit_value = 2;
	}
	else
		*exit_value %= 256;
	return (*exit_value);
}
