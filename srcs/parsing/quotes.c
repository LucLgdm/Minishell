/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:35:06 by andrean           #+#    #+#             */
/*   Updated: 2025/03/18 12:43:21 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quotes(char *str, int *i, char **word)
{
	++(*i);
	while (str[*i] && str[*i] != CHAR_S_QUOTE)
	{
		strncat(*word, str[*i], 1);
	}
}

char	**manage_quotes(char **prev_words, char *str)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			single_quotes;
		if (str[i] == '"')
			double_quotes;
		if (!str[i] || str[i] == ' ')
			end_word;
	}
}