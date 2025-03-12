/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:29:58 by andrean           #+#    #+#             */
/*   Updated: 2025/03/12 15:51:59 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_one(char *str)
{
	char	*equalsign;
	char	*key;

	equalsign = ft_strchr(str, '=');
	if (!equalsign)
		return ;
	key = ft_substr(str, 0, equalsign - str);
	if (!key)
		;//malloc error
	
}

void	export(t_ast *node)
{
	int	arg_nb;
	int	count;

	arg_nb = get_arg_nb(node);
	count = 0;
	while (++count < get_arg_nb)
	{
		
	}
}