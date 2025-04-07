/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:45:13 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/07 12:52:25 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	ft_free_token(t_token **token, int freesub)
{
	if (!token || !*token)
		return ;
	if ((*token)->sub_token && freesub)
		ft_free_token(&(*token)->sub_token, 1);
	if (token && *token)
		if ((*token)->next)
			ft_free_token(&(*token)->next, freesub);
	if (token && (*token) && (*token)->value)
	{
		free((*token)->value);
		(*token)->value = NULL;
	}
	if (token && *token)
	{
		free(*token);
		*token = NULL;
	}
}
