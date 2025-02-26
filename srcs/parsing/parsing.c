/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 11:08:36 by andrean           #+#    #+#             */
/*   Updated: 2025/02/26 15:47:34 by andrean          ###   ########.fr       */
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
			skipquote(line, &i, '\'');
		else if (line[i] == '$')
			subdollarmanagement(line, &i, &j, &newline);
		else
			i++;
	}
	newline	= ft_strjoinfree(newline, ft_substr(line, j, i - j));
	free(line);
	return (newline);
}

int manage_pipe(char *line, int *i, int *j)
{
	int	j_start;

	j_start = *j;
	j_start++;
	while (ft_isspace(line[j_start]))
	{
		printf("not here\n");
		(j_start)++;
	}
	if (line[j_start] == '|')
	{
		printf("i: %c/%i, j: %c/%i\n", line[*i], *i, line[*j], *j);
		return (1);
	}
	(*i)++;
	return (0);
}

int	create_sub(char *line, int *i, int *j, t_lst **word_lst)
{
	char	*newline;
	t_lst	*sub;

	if (line[*i] == '(')
		if (manage_pipe(line, i, j))
			return (0);
	newline = ft_substr(line, *i, *j - (*i));
	sub = ft_lstnewword(newline, 1);
	*(sub->sub) = separate_line(newline);
	sub->word_type = -1;
	ft_lstback(word_lst, sub);
	return (1);
	
}

void	manage_and_or(char *line, int *i, int *j, t_lst **word_lst)
{
	if (!line[*j] && *i == 0 && line[*i] == '(')
	{
		printf("je passe par la, pouet\n");
		*word_lst = separate_one_pipe(line);
		printf("AVANT i : %d, j : %d\n", *i, *j);
		*i = *j;
		printf("APRES i : %d, j : %d\n", *i, *j);
		return ;
	}
	if (!line[*j] && !(*word_lst))
	{
		*word_lst = parse_line(line);
		*i = *j;
		return ;
	}
	if (!line[*j] && *j == *i)
		return ;
	if (*j != *i)
	{
		create_sub(line, i, j, word_lst);
		*i = *j;
	}
	ft_lstback(word_lst, ft_lstnewword(subline(line, i, j), 0));
}

void	manage_parenthesis(char *line, int *i, int *j, t_lst **word_lst)
{
	int		open_count;

	open_count = 1;
	if ((!(*word_lst) || (ft_lstlastword(*word_lst))->word_type != -1))
	{
		printf("pouet\n");
		while (line[(*j)] && open_count > 0)
		{
			(*j)++;
			if (line[*j] == '(')
				open_count++;
			if (line[*j] == ')')
				open_count--;
		}
		if (!line[*j] && open_count)
		{
			printf("j: %d->%c, count: %d\n", *j, line[*j], open_count);
			exit(0);//parse error
		}
		if (!create_sub(line, i, j, word_lst))
			return ;
		*i = ++(*j);
		ft_skipspaces(line, i, j);
		if (!istoken(line + *j) && line[*j])
			exit(0);//parse error
	}
	else if (line[*i] == '(')
		(*j)++;
	else
		exit(0);//parse error
}

t_lst	*split_word(t_lst *node)
{
	t_lst	*newword;
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	word = NULL;
	newword = NULL;
	node->word = dollarmanagement(node->word);
	while (node->word[i] != '\0')
	{
		ft_skipspaces(node->word, &i, &j);
		if ((!node->word[j]) || ft_isspace(node->word[j]))
		{
			ft_lstback(&newword, ft_lstnewword(ft_strjoinfree(word, subline(node->word, &i, &j)), 1));
			word = NULL;
			i = j;
		}
		else if (node->word[j] == '\'' || node->word[j] == '"')
		{
			word = quotemanagement(node->word, &i, &j, word);
			if (!node->word[j] || ft_isspace(node->word[j]))
			{
				ft_lstback(&newword, ft_lstnewword(word, 1));
				word = NULL;
			}
		}
		else
			j++;
	}
	return (newword);
}

void	get_dollar_in_word(t_lst **word)
{
	t_lst	*tmp;

	tmp = *word;
	*word = split_word(*word);
	printf("tmp: %p, next: %p, prev: %p\n", tmp, *(tmp->next), *(tmp->prev));
	printf("word: %p, next: %p, prev->%p\n", (*word), *((*word)->next), *((*word)->prev));
	if (*(tmp->prev))
		printf("tmp prev prev?%p\n", *((*(tmp->prev))->prev));
	if (!*word)
	{
		if (*(tmp->prev))
			(*tmp->prev)->next = tmp->next;
		if (*(tmp->next))
			(*tmp->next)->prev = tmp->prev;
		*word = *(tmp->next);
	}
	else
	{
		if (*(tmp->next))
			*((*tmp->next)->prev) = *word;
		printf("before: word-> %p, prev->%p\n", (*word), *((*word)->prev));
		(*word)->prev = tmp->prev;
		printf("middle: word-> %p, prev->%p\n", (*word), *((*word)->prev));
		(ft_lstlastword(*word))->next = tmp->next;
	}
	ft_lstdeloneword(tmp);
}

void	get_dollar_in_struct(t_lst **words)
{
	while (*words)
	{
		if ((*words)->word_type == -1)
			get_dollar_in_struct((*words)->sub);
		if ((*words)->word_type == 0)
			get_dollar_in_word(words);
		if (*words)
			words = (*words)->next;
	}
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
		if ((istoken(line + j) || (!line[j]) || ft_isspace(line[j])) && (j != i || istoken(line + j)))
		{
			ft_lstback(&word_lst, ft_lstnewword(ft_strjoinfree(word, subline(line, &i, &j)), j - i));
			word = NULL;
			i = j;
		}
		else if (line[j] == '\'')
			skipquote(line, &j, '\'');
		else if (line[j] == '"')
			skipquote(line, &j, '"');
		else
			j++;
	}
	return (word_lst);
}

t_lst	*separate_line(char *line)
{
	t_lst	*word_lst;
	int		i;
	int		j;

	i = 0;
	j = 0;
	word_lst = NULL;
	while (line[i] != '\0')
	{
		printf("i: %d, j: %d\n", i, j);
		if (i == j)
			ft_skipspaces(line, &i, &j);
		if (line[j] == '(')
			manage_parenthesis(line, &i, &j, &word_lst);
		else if (is_and_or(line + j) || (!line[j]))
			manage_and_or(line, &i, &j, &word_lst);
		else if (line[j] == '"')
			skipquote(line, &j, '"');
		else if (line[j] == '\'')
			skipquote(line, &j, '\'');
		else
			j++;
	}
	return (word_lst);
}