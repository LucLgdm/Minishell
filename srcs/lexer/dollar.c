/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:14:31 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/18 12:29:34 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	handle_dollar(t_token **token_lst, t_hashtable *env_ht)
// {
// 	t_token	*tmp;

// 	tmp = *token_lst;
// 	if (!tmp)
// 		return (1);
// 	while (tmp)
// 	{
// 		if (tmp->token_type == TOKEN_PARENTHESES)
// 			handle_dollar(&tmp->sub_token, env_ht);
// 		else if (tmp->token_type == TOKEN_WORD)
// 			tmp->value = ft_expand(tmp->value, env_ht);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }

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
		if (word[i] == CHAR_S_QUOTE)
			ft_single_quote(&new_word, word, &i);
		else if (word[i] == CHAR_D_QUOTE)
			ft_double_quote(&new_word, word, &i, env_ht);
		else if (word[i] == CHAR_DOLLAR)
		{
			var_name = ft_extract_var_name(word, &i);
			// printf("Var name extracted : %s\n", var_name);
			if (strcmp(var_name, "") == 0)
				ft_strncat(&new_word, "$", 1);
			env_value = ft_get_env_value(var_name, env_ht);
			// printf("Env value getted : %s\n", env_value);
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
		;//unclosed quotes;
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
		;//unclosed quotes;
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

void	ft_append_char(char **new_word, char c)
{
	char	*tmp;
	int		len;

	if (!new_word || !*new_word)
		return ;
	len = ft_strlen(*new_word);
	tmp = malloc(len + 2);
	if (!tmp)
		return ;
	ft_strcpy(tmp, *new_word);
	tmp[len] = c;
	tmp[len + 1] = '\0';
	free(*new_word);
	*new_word = tmp;
}

char	*ft_get_env_value(char *key, t_hashtable *env_ht)
{
	t_element	*elem;

	elem = ft_get_element(env_ht, key);
	if (elem)
		return (elem->value);
	if (!env_ht)
	{
		elem = ft_get_element((*get_world())->new_env, key);
		if (elem)
			return (elem->value);
	}
	elem = ft_get_element((*get_world())->hidden_vars, key);
	if (elem)
		return (elem->value);
	return (NULL);
}

char	*ft_extract_var_name(char *str, int *i)
{
	int	start;
	int	len;

	start = *i + 1;
	len = 0;
	while ((str[start + len] && (ft_isalnum(str[start + len]) || str[start
					+ len] == '_')) && !(ft_isdigit(str[start])))
		len++;
	if (ft_isdigit(str[start]))
		while (str[start + len] && ft_isdigit(str[start + len]))
			len++;
	*i += len;
	return (ft_substr(str, start, len));
}
