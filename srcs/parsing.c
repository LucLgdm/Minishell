/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:36 by andrean           #+#    #+#             */
/*   Updated: 2025/02/18 14:44:15 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotemanagement(char *line, int *i, int *j, char *word)
{
	if (j != i)
		word = ft_strjoinfree(word, subline(line, i, j, 1));
	*i = (*j)++;
	while (line[*j] != '\0' && line[*i] != line[*j])
		(*j)++;
	if (line[*j] == '\0')
		*j = *i + 1;
	else
	{
		(*i)++;
		if (line[*j] == '\'')
			word = ft_strjoinfree(word, subline(line, i, j, 0));
		else if (line[*j] == '"')
			word = ft_strjoinfree(word, subline(line, i, j, 1));
		*i = ++(*j);
	}
	return (word);
}

//refaire substr pour gerer '$'
t_lst	*parse_line(char *line)
{
	t_lst	*word_lst;
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	word = NULL;
	while (line[i] != '\0')
	{
		if (ft_isspace(line[i]))
			ft_skipspaces(line, &i, &j);
		else if ((istoken(line + j) || isspace(line[j])) || !line[j])
		{
			ft_lstback(&word_lst, ft_lstnewword(ft_strjoinfree(word,
						subline(line, &i, &j, 1)), j - i));
			word = NULL;
			i = j;
		}
		else if (line[j] == '"' || line[j] == '\'')
		{
			word = quotemanagement(line, &i, &j, word);
			if (istoken(line + i) || isspace(line[j]) || !line[j])
			{
				ft_lstback(&word_lst, ft_lstnewword(word, 1));
				word = NULL;
			}
		}
		else
			j++;
	}
	return (word_lst);
}
