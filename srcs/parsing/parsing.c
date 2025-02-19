/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:36 by andrean           #+#    #+#             */
/*   Updated: 2025/02/18 17:54:36 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotemanagement(char *line, int *i, int *j, char *word)
{
	if (j != i)
		word = ft_strjoinfree(word, subline(line, i, j));
	*i = (*j)++;
	while (line[*j] != '\0' && line[*i] != line[*j])
		(*j)++;
	if (line[*j] == '\0')
		*j = *i + 1;
	else
	{
		(*i)++;
			word = ft_strjoinfree(word, subline(line, i, j));
		*i = ++(*j);
	}
	return (word);
}

void	skipsimplequote(char *line, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (line[*i] != '\'' || line[*i] != '\0')
		(*i)++;
	if (!line[*i])
		(*i) = start;
	(*i)++;
}

void	subdollarmanagement(char *line, int *i, int *j, char **newline)
{
	char	*vardup;

	*newline = ft_strjoinfree(*newline, ft_substr(line, (*j), (*i) - (*j)));
	(*j) = (*i) + 1;
	if (ft_isdigit(line[(*j)]))
		vardup = ft_substr(line, (*j), 1);
	else if (ft_isalnum(line[(*j)]) || line[(*j)] == '_')
	{
		while (ft_isalnum(line[(*j)]) || line[(*j)] == '_')
			(*j)++;
		vardup = ft_substr(line, (*i) + 1, (*j) - ((*i) + 1));
	}
	if (!vardup && (ft_isalnum(line[(*i) + 1]) || line[(*i) + 1] == '_'))
	{} //malloc error
	else if (vardup)
	{
		printf("%s\n", vardup);
		*newline = ft_strjoinfree(*newline, ft_strdup(getenv(vardup)));
		free(vardup);
		(*i) = (*j);
	}
	else
		(*j) = (*i)++;
}

char	*dollarmanagement(char *line)
{
	char	*vardup;
	char	*newline;
	int		i;
	int		j;

	i = 0;
	j = 0;
	newline = NULL;
	while (line[i])
	{
		if (line[i] == '\'')
			skipsimplequote(line, &i);
		else if (line[i] == '$')
			subdollarmanagement(line, &i, &j, &newline);
		else
			i++;
	}
	newline	= ft_strjoinfree(newline, ft_substr(line, j, i - j));
	free(line);
	return (newline);
}

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
						subline(line, &i, &j)), j - i));
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
