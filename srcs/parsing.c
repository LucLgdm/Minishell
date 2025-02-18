/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:36 by andrean           #+#    #+#             */
/*   Updated: 2025/02/17 17:17:03 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotemanagement(char *line, int *i, int *j, char *word)
{
	if (j != i)
		word = ft_strjoinfree(word, ft_substr(line, *i, *j - *i));
	*i = *j++;
	while (line[*j] != '\n' && line[*i] != line[*j])
		*j++;
	if (line[*j] == '\n')
		*j = *i + 1;
	else
	{
		if (line[*i] == '\'')
			word = ft_strjoinfree(word, ft_substr(line, *i + 1, *j - *i - 1, 0));
		else if (line[*i] == '"')
			word = ft_strjoinfree(word, ft_substr(line, *i + 1, *j - *i - 1, 1));
		*i = ++*j;
	}
	return (word);
}

//refaire substr pour gerer '$'
void	parse_line(char *line)
{
	t_lst	*word_lst;
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	word = NULL;
	while (line[i] != '\n')
	{
		if (isspace(line[i]))
			ft_skipspace(line, &i, &j);
		else if ((istoken(line + j) || isspace(line[j])) && j != i)
			ft_lstback(&word_lst, ft_lstnewword(ft_strjoinfree(word,
						ft_substr(line, i, j - i, 1))));
		else if (line[j] == '"' || line[j] == '\'')
		{
			word = quotemanagement(line, &i, &j, word);
			if (line[i] == '\n')
				ft_lstback(&word_lst, ft_lstnewword(word));
		}
		else
			j++;
	}
}
