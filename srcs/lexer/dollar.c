/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-merc <lde-merc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:14:31 by lde-merc          #+#    #+#             */
/*   Updated: 2025/03/04 14:31:24 by lde-merc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_dollar(t_token **token_lst)
{
	t_token	*tmp;
	char	*new_word;

	tmp = *token_lst;
	while (tmp)
	{
		if (tmp->token_type == TOKEN_WORD && ft_strchr(tmp->value, CHAR_DOLLAR))
		{
			new_word = ft_expand(tmp->value);
			free(tmp->value);
			tmp->value = new_word;
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*ft_expand(char *word)
{
	int		i;
	char	*new_word;

	new_word = ft_strdup("");
	i = -1;
	while (word[++i])
	{
		if (word[i] == CHAR_S_QUOTE)
			ft_single_quote(&new_word, word, &i);
		else if (word[i] == CHAR_D_QUOTE)
			ft_double_quote(&new_word, word, &i);
		else if (word[i] == CHAR_DOLLAR)
			ft_replace(&new_word, word, &i);
		else
			ft_append_char(&new_word, word[i]);
	}
	return (new_word);
}

void	ft_append_char(char **new_word, char c)
{
	char	*tmp;
	int		len;

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

void	ft_single_quote(char **new_word, char *word, int *i)
{
	int	start;

	start = ++(*i);
	while (word[*i] && word[*i] != CHAR_S_QUOTE)
		(*i)++;
	ft_strncat(new_word, &word[start], *i - start);
}

void	ft_double_quote(char **new_word, char *word, int *i)
{
	int	start;

	start = ++(*i);
	while (word[*i] && word[*i] != CHAR_D_QUOTE)
	{
		if (word[*i] == CHAR_DOLLAR)
			ft_replace(new_word, word, i);
		else
			ft_append_char(new_word, word[(*i)++]);
	}
}

void	ft_replace(char **new_word, char *word, int *i)
{
	int		start;
	char	var_name[256];
	int		j;
	char	*value;

	j = 0;
	start = ++(*i);
	while (word[*i] && (ft_isalnum(word[*i]) || word[*i] == '_'))
		var_name[j++] = word[(*i)++];
	var_name[j] = '\0';
	value = get_env_value(var_name, get_world()->env);
	if (value)
		ft_strcat(*new_word, value);
	else
		ft_strcat(*new_word, "");
	(*i)--;
}

char	*get_env_value(char *name, t_list *env_list)
{
	t_list *tmp;
	char *env_var;
	size_t name_len;

	tmp = env_list;
	name_len = strlen(name);
	while (tmp)
	{
		env_var = tmp->content;
		if (strncmp(env_var, name, name_len) == 0 && env_var[name_len] == '=')
			return (env_var + name_len + 1);
		tmp = tmp->next;
	}
	return (NULL);
}
