/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 09:14:38 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_tree(t_world *world)
{
	t_token	*token_lst;

	token_lst = tokenization_token(world->prompt);
	if (!token_lst)
		return ;
	world->tokenlist = token_lst;
	world->tree = parse_token(token_lst);
}
