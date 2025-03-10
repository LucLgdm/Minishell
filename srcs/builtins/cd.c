/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:34:49 by andrean           #+#    #+#             */
/*   Updated: 2025/03/10 15:51:05 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  /!\  ne pas creer de process avant d'appeler cette fonction, sinon inutile.
 
int	ft_cd(t_ast *node)
{
	if (get_arg_nb(node) > 2)
		;//too many args
	if (get_arg_nb(node) == 1)
		;// a verifier chdir("/");
	else
		chdir(node->cmd[1]);
}