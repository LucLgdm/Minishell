/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:35:06 by andrean           #+#    #+#             */
/*   Updated: 2025/03/21 17:17:47 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	quotes(char *str, int *i, char **word, char quote_type)
{
	++(*i);
	while (str[*i] && str[*i] != quote_type)
	{
		if (word)
			ft_strncat_stop(word, str + (*i), 1);
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
		tmp = ft_catchartab_stop(*new_words, tab, ft_arraylen(*new_words));
		if (trunclst)
		{
			*new_words = manage_wildcards(tmp, 0, *trunclst);
			ft_free_array(*trunclst);
		}
		else
			*new_words = tmp;
		free(*word);
		*word = ft_strdup_stop("");
	}
}

void	get_trunclst_loop(char ***trunclst, char **wild, char **word, char *str)
{
	int		i;
	char	**tmp;

	i = -1;
	while (str[++i])
	{
		if (str + i == *wild)
		{
			end_word(word, trunclst, NULL);
			tmp = onewildtab();
			*trunclst = ft_catchartab_stop(*trunclst, tmp,
					ft_arraylen(*trunclst));
			*wild = ft_strchr_outofquotes(str + i + 1, '*');
		}
		else if (str[i] == '"' || str[i] == '\'')
			quotes(str, &i, word, str[i]);
		else
			ft_strncat_stop(word, str + i, 1);
	}
}

char	**get_trnclst(char *str)
{
	char	**trunclst;
	char	*wild;
	char	*word;

	if (!str)
		return (NULL);
	wild = ft_strchr_outofquotes(str, '*');
	if (!wild)
		return (NULL);
	trunclst = ft_calloc_stop(sizeof(char *), 1);
	word = ft_strdup_stop("");
	get_trunclst_loop(&trunclst, &wild, &word, str);
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
	word = ft_strdup_stop("");
	new_words = ft_calloc_stop(sizeof(char *), 1);
	trunclst = get_trnclst(str);
	while (str[++i])
	{
		if (str[i] == '\'')
			quotes(str, &i, &word, '\'');
		else if (str[i] == '"')
			quotes(str, &i, &word, '"');
		else
			ft_strncat_stop(&word, str + i, 1);
	}
	end_word(&word, &new_words, &trunclst);
	if (!prev_words)
		prev_words = ft_calloc_stop(sizeof(char *), 1);
	trunclst = ft_catchartab_stop(prev_words, new_words, index);
	return (free(word), trunclst);
}
