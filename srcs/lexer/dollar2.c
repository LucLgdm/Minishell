/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 12:05:36 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/21 18:27:11 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_append_char(char **new_word, char c)
{
	char	*tmp;
	int		len;

	if (!new_word || !*new_word)
		return ;
	len = ft_strlen(*new_word);
	tmp = ft_calloc_stop(len + 2, 1);
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

	if (env_ht)
	{
		elem = ft_get_element(env_ht, key);
		if (elem)
			return (elem->value);
	}
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
	if (str[start] == '?')
	{
		(*i)++;
		return (ft_strdup_stop("?"));
	}
	while ((str[start + len] && (ft_isalnum(str[start + len]) || \
	str[start + len] == '_')) && !(ft_isdigit(str[start])))
		len++;
	if (ft_isdigit(str[start]))
		while (str[start + len] && ft_isdigit(str[start + len]))
			len++;
	*i += len;
	return (ft_substr_stop(str, start, len));
}
