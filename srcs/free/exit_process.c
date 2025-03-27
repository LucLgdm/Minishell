/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 12:23:11 by andrean           #+#    #+#             */
/*   Updated: 2025/03/27 14:09:45 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_process(int exit_status)
{
	t_world	*world;

	world = (*get_world());
	free_all(&world);
	exit(exit_status);
}
