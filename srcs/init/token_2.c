/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:00:59 by lde-merc          #+#    #+#             */
/*   Updated: 2025/02/27 14:24:57 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quote(char *prompt, char **tmp_token, int *i, char **token, int *j)
{
	char	quote_char;
	int		k;

	if (prompt[*i] == '"' || prompt[*i] == '\'')
	{
		quote_char = prompt[*i];
		(*tmp_token)[0] = quote_char;
		k = 1;
		(*i)++;
		while (prompt[*i] && prompt[*i] != quote_char)
		{
			(*tmp_token)[k++] = prompt[*i];
			(*i)++;
		}
		if (prompt[*i] == quote_char)
		{
			(*tmp_token)[k++] = quote_char;
			(*i)++;
		}
		(*tmp_token)[k] = '\0';
		token[(*j)++] = ft_strdup(*tmp_token);
	}
}
