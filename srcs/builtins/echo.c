/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:02:39 by andrean           #+#    #+#             */
/*   Updated: 2025/03/10 15:14:29 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '-')
		return (0);
	while (str[++i])
		if (str[i] != 'n')
			return (0);
	return (1);
}

void	ft_echo(t_ast *node)
{
	int	isn;
	int	i;

	isn = 0;
	i = -1;
	while (is_n_flag(node->cmd[++i]))
		isn = 1;
	while (node->cmd[i])
	{
		printf("%s", node->cmd[i]);
		if (node->cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!isn)
		printf("\n");
	exit(EXIT_SUCCESS);
}
