/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:35:06 by andrean           #+#    #+#             */
/*   Updated: 2025/03/19 17:24:45 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr_outofquotes(char *str, char c)
{
	int	i;

	i = 0;
	if (!c || !str)
		return (str);
	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	return (NULL);
}

void	quotes(char *str, int *i, char **word, char quote_type)
{
	++(*i);
	while (str[*i] && str[*i] != quote_type)
	{
		ft_strncat(word, str + (*i), 1);
		(*i)++;
	}
}

void	end_word(char **word, char ***new_words, char ***trunclst)
{
	char	**tab;
	char	**tmp;

	if (**word)
	{
		tab = onelinetab(*word);
		tmp = ft_catchartab(*new_words, tab, ft_arraylen(*new_words));
		ft_free_array(*new_words);
		if (trunclst)
		{
			*new_words = manage_wildcards(tmp, 0, *trunclst);
			ft_free_array(*trunclst);
		}
		else
			*new_words = tmp;
		free(*word);
		*word = ft_strdup("");
	}
}

char	**get_trnclst(char *str)
{
	char	**trunclst;
	char	*wild;
	char	*word;
	int		i;

	i = -1;
	if (!str)
		return (NULL);
	wild = ft_strchr_outofquotes(str, '*');
	if (!wild)
		return (NULL);
	trunclst = ft_calloc(sizeof(char *), 1);
	word = ft_strdup("");
	while (str[++i])
	{
		if (str + i == wild)
		{
			end_word(&word, &trunclst, NULL);
			trunclst = ft_catchartab(trunclst,
					onewildtab(), ft_arraylen(trunclst));
			wild = ft_strchr_outofquotes(str + i + 1, '*');
		}
		else if (str[i] == '"' || str[i] == '\'')
			quotes(str, &i, &word, str[i]);
		else
			ft_strncat(&word, str + i, 1);
	}
	if (*word)
		end_word(&word, &trunclst, NULL);
	free(word);
	return (trunclst);
}




char	**manage_quotes(char **prev_words, char *str, int index)
{
	int		i;
	char	*word;
	char	**new_words;
	char	**trunclst;

	i = -1;
	if (!str)
		return (prev_words);
	word = ft_strdup("");
	new_words = ft_calloc(sizeof(char *), 1);
	trunclst = get_trnclst(str);
	while (str[++i])
	{
		if (str[i] == '\'')
			quotes(str, &i, &word, '\'');
		else if (str[i] == '"')
			quotes(str, &i, &word, '"');
		else
			ft_strncat(&word, str + i, 1);
	}
	end_word(&word, &new_words, &trunclst);
	if (!prev_words)
		prev_words = ft_calloc(sizeof(char *), 1);
	trunclst = ft_catchartab(prev_words, new_words, index);
	ft_free_array(prev_words);
	return (trunclst);
}