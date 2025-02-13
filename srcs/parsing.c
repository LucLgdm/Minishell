/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:36 by andrean           #+#    #+#             */
/*   Updated: 2025/02/13 16:01:04 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//gère pas '$'
void	parse_line(char *line)
{
	t_lst	*word_lst;
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	word = NULL;
	while (!isend(line[i]))
	{
		while (isspace(line[i]))
			j = ++i;
		while (!(isspace(line[j]) || isend(line[j]) || isoperator(line[j]))
			&& line[j] != '"' && line[j] != '\'')
			j++;
		if ((isspace(line[j]) || isend(line[j]) || isoperator(line[j])))
			ft_lstback(&word_lst, ft_lstnewword(ft_strjoinfree(word,
						ft_substr(line, i, j - i))));
		i = j;
		else 
		{
			word = ft_strjoinfree(word, ft_substr(line, i, j - i));
			j++;
			while (!isend(line[j]) && line[i] != line[j])
				j++;
			if (isend(line[j]).)
				j = i + 1;
			else
			{
				word = ft_strjoinfree(word, ft_substr(line, i + 1, j - i - 1));
				i = ++j;
				if (isend(line[i]))
					ft_lstback(&word_lst, ft_lstnewword(word));
			}
		}
	}
}