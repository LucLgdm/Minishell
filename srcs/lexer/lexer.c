/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:25:40 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/28 14:30:19 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*tokenization(char *prompt)
{
	t_token *token_lst;
	int len_token;

	token_lst = NULL;
	len_token = 0;
	while (*prompt)
	{
		if (ft_isspace(*prompt))
			prompt++;
		else
		{
			len_token = token_len(prompt);
			token_lst = fill_token(token_lst, prompt, len_token);
			prompt += len_token;
		}
	}
	return (token_lst);
}