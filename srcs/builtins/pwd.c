/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:51:35 by andrean           #+#    #+#             */
/*   Updated: 2025/03/20 11:42:19 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_ast *node)
{
	char	*wd;

	(void)node;
	wd = ft_calloc(sizeof(char), 250);
	if (!wd)
		return (1);
	getcwd(wd, 250);
	printf("%s\n", wd);
	free(wd);
	return (0);
}
