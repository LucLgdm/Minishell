/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:36 by andrean           #+#    #+#             */
/*   Updated: 2025/02/20 15:28:22 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	while (line[*i] != '\'' && line[*i] != '\0')
		(*i)++;
	if (!line[*i])
		(*i) = start;
	(*i)++;
}

void	subdollarmanagement(char *line, int *i, int *j, char **newline)
{
	char	*vardup;

	vardup = NULL;
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
		*newline = ft_strjoinfree(*newline, ft_strdup(getenv(vardup)));
		free(vardup);
		(*i) = (*j);
	}
	else
		(*j) = (*i)++;
}

char	*dollarmanagement(char *line)
{
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

// t_lst	*parse_line(char *line)
// {
// 	t_lst	*word_lst;
// 	int		i;
// 	int		j;
// 	char	*word;

// 	i = 0;
// 	j = 0;
// 	word = NULL;
// 	word_lst = NULL;
// 	while (line[i] != '\0')
// 	{
// 		if (ft_isspace(line[i]))
// 			ft_skipspaces(line, &i, &j);
// 		else if ((istoken(line + j) || ft_isspace(line[j])) || !line[j])
// 		{
// 			ft_lstback(&word_lst, ft_lstnewword(ft_strjoinfree(word, subline(line, &i, &j)), j - i));
// 			word = NULL;
// 			i = j;
// 		}
// 		else if (line[j] == '"' || line[j] == '\'')
// 		{
// 			word = quotemanagement(line, &i, &j, word);
// 			if (istoken(line + i) || ft_isspace(line[j]) || !line[j])
// 			{
// 				ft_lstback(&word_lst, ft_lstnewword(word, 1));
// 				word = NULL;
// 			}
// 		}
// 		else
// 			j++;
// 	}
// 	return (word_lst);
// }

void	manage_parenthesis(char *line, int *i, int *j, t_lst **word_lst)
{
	int		open_count;
	char	*newline;
	t_lst	*sub;

	open_count = 1;
	if (*j == *i && (!(*word_lst) || (ft_lstlastword(*word_lst))->word_type > 4))
	{
		while (line[++(*j)] && open_count > 0)
		{
			if (line[*j] == '(')
				open_count++;
			if (line[*j] == ')')
				open_count--;
		}
		(*j)--;
		if (!line[*j])
			;//parse error
		newline = ft_substr(line, *i + 1, *j - (*i + 1));
		sub = ft_lstnewword(newline, 1);
		sub->sub = parse_line(newline);
		sub->word_type = -1;
		ft_lstback(word_lst, sub);
		*i = ++(*j);
		ft_skipspaces(line, i, j);
		if (!is_and_or_pipe(line + *j) && line[*j])
			;//parse error
	}
	else
		;//parse error
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
	word_lst = NULL;
	while (line[i] != '\0')
	{
		ft_skipspaces(line, &i, &j);
		if (line[j] == '(')
			manage_parenthesis(line, &i, &j, &word_lst);
		if (istoken(line + j) || (!line[j]) || ft_isspace(line[j]))
		{
			ft_lstback(&word_lst, ft_lstnewword(ft_strjoinfree(word, subline(line, &i, &j)), j - i));
			word = NULL;
			i = j;
		}
		else if (line[j] == '"' || line[j] == '\'')
		{
			word = quotemanagement(line, &i, &j, word);
			if (istoken(line + i) || !line[j] || ft_isspace(line[j]))
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
