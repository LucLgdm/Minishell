/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:34 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 19:05:41 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_tree(t_world **world)
{
	t_token	*token_lst;

	token_lst = tokenization_token((*world)->prompt);
	if (!token_lst)
		return ;
	print_token(token_lst, 0);
	(*world)->tokenlist = token_lst;
	print_token((*world)->tokenlist, 0);
	(*world)->tree = parse_token(token_lst);
	print_token((*world)->tokenlist, 0);
}
