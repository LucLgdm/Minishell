/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:14:31 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/20 12:08:36 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_good_quote(char *word, char *new_word, int i,
		t_hashtable *env_ht)
{
	if (word[i] == CHAR_S_QUOTE)
		ft_single_quote(&new_word, word, &i);
	if (word[i] == CHAR_D_QUOTE)
		ft_double_quote(&new_word, word, &i, env_ht);
}

char	*ft_expand(char *word, t_hashtable *env_ht)
{
	int		i;
	char	*new_word;
	char	*env_value;
	char	*var_name;

	new_word = ft_strdup("");
	i = -1;
	while (word[++i])
	{
		if (word[i] == CHAR_D_QUOTE || word[i] == CHAR_S_QUOTE)
			ft_good_quote(word, new_word, i, env_ht);
		else if (word[i] == CHAR_DOLLAR)
		{
			var_name = ft_extract_var_name(word, &i);
			if (strcmp(var_name, "") == 0)
				ft_strncat(&new_word, "$", 1);
			env_value = ft_get_env_value(var_name, env_ht);
			free(var_name);
			if (env_value)
				ft_strncat(&new_word, env_value, ft_strlen(env_value));
		}
		else
			ft_strncat(&new_word, &word[i], 1);
	}
	return (new_word);
}

void	ft_single_quote(char **new_word, char *word, int *i)
{
	ft_strncat(new_word, &word[(*i)++], 1);
	while (word[*i] && word[*i] != CHAR_S_QUOTE)
	{
		ft_strncat(new_word, &word[(*i)], 1);
		(*i)++;
	}
	if (!word[*i])
		perror("Missing quote");
	else
		ft_strncat(new_word, &word[(*i)], 1);
}

void	ft_double_quote(char **new_word, char *word, int *i,
		t_hashtable *env_ht)
{
	ft_strncat(new_word, &word[(*i)++], 1);
	while (word[*i] && word[*i] != CHAR_D_QUOTE)
	{
		if (word[*i] == CHAR_DOLLAR)
			ft_replace(new_word, word, i, env_ht);
		else
			ft_append_char(new_word, word[(*i)++]);
	}
	if (!word[*i])
		perror("Missing quote");
	else
		ft_strncat(new_word, &word[(*i)], 1);
}

void	ft_replace(char **new_word, char *word, int *i, t_hashtable *env_ht)
{
	int		start;
	char	var_name[256];
	int		j;
	char	*value;

	j = 0;
	value = NULL;
	start = ++(*i);
	while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
		var_name[j++] = word[(*i)++];
	var_name[j] = '\0';
	value = ft_get_env_value(var_name, env_ht);
	if (value)
		ft_strcat(*new_word, value);
	else
		ft_strcat(*new_word, "");
}
