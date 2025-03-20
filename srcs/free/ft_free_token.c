/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:45:13 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 17:27:02 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	ft_free_token(t_token **token)
{
	if (!token || !*token)
		return ;
	ft_free_token(&(*token)->sub_token);
	ft_free_token(&(*token)->next);
	free((*token)->value);
	free(*token);
	*token = NULL;
}
