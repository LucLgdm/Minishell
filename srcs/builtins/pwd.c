/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:51:35 by andrean           #+#    #+#             */
/*   Updated: 2025/03/13 16:03:02 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_ast *node)
{
	char *wd;

	(void)node;
	wd = ft_calloc(sizeof(char), 250);
	if (!wd)
		;//error
	getcwd(wd, 250);
	printf("%s\n", wd);
	free(wd);
	return (0);
}
