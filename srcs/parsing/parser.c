/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:29:07 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/06 11:40:04 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_ast	*parse_token(t_token *token)
{
	t_ast	*root;

	root = NULL;
	ft_create_tree(&root, token);
	return (root);
}
