/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_with_parenthesis.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:12:25 by andrean           #+#    #+#             */
/*   Updated: 2025/02/25 15:25:53 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_sub_with_pipe(char *line, int *i, int *j, t_lst **word_lst)
{
	char	*newline;
	t_lst	*sub;

	newline = ft_substr(line, *i, *j - (*i));
	sub = ft_lstnewword(newline, 1);
	*(sub->sub) = separate_line(newline);
	sub->word_type = -1;
	ft_lstback(word_lst, sub);
	return (1);
	
}

void	manage_parenthesis_with_pipe(char *line, int *i, int *j, t_lst **word_lst)
{
	int		open_count;

	open_count = 1;
	if (*j == *i && (!(*word_lst) || (ft_lstlastword(*word_lst))->word_type != -1))
	{
		while (line[(*j)] && open_count > 0)
		{
			(*j)++;
			if (line[*j] == '(')
				open_count++;
			if (line[*j] == ')')
				open_count--;
		}
		if (!line[*j])
			;//parse error
		if (!create_sub_with_pipe(line, i, j, word_lst))
			return ;
		*i = ++(*j);
		ft_skipspaces(line, i, j);
		if (!istoken(line + *j) && line[*j])
			;//parse error
		ft_lstback(word_lst, ft_lstnewword(subline(line, i, j), 0));
	}
	else if (line[*i] == '(')
		(*j)++;
	else
		;//parse error
}

t_lst	*separate_one_pipe(char *line)
{
	t_lst	*word_lst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word_lst = NULL;
	while (line[i] != '\0')
	{
		if (i == j)
			ft_skipspaces(line, &i, &j);
		if (line[j] == '(')
			manage_parenthesis_with_pipe(line, &i, &j, &word_lst);
		else if (line[j] == '"')
			skipquote(line, &j, '"');
		else if (line[j] == '\'')
			skipquote(line, &j, '\'');
		else
			j++;
	}
	return (word_lst);
}