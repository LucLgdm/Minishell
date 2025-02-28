/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:26:15 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/28 11:05:17 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_node	*parse_token(char **token, int *i)
{
	t_node	*root;
	int		j;
	int		k;

	j = *i;
	k = 0;
	while(!ft_isoperator(token[j][0]))
	{
		if (token[j][0] == '('){
			// sub_token = tokenization()
			// sub_tree = parse_token(sub_token, 0)
		}
		root->cmd[k] = ft_strdup(token[k + j]);
		k++;
	}	
	return (root);
}
