/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrean <andrean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 08:30:52 by lde-merc          #+#    #+#             */
/*   Updated: 2025/04/04 16:06:11 by andrean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_and_quit(char **split, char *key, char *value)
{
	ft_free_array(split);
	safe_free(key);
	safe_free(value);
	stop_when_calloc_fail();
}

void	ft_env_to_hashtable(char **env, t_hashtable *env_hastable)
{
	int		i;
	char	**split;
	char	*key;
	char	*value;

	i = -1;
	while (env[++i])
	{
		split = ft_split_stop(env[i], '=', 0);
		if (split[0])
			key = ft_strdup(split[0]);
		if (split[1])
			value = ft_strdup(split[1]);
		else
			value = ft_strdup("");
		if (!key || !value)
			ft_free_and_quit(split, key, value);
		ft_add_element(&env_hastable, key, value);
		free(key);
		free(value);
		ft_free_array(split);
	}
}

void	ft_create_new_env(t_hashtable **hashtable)
{
	char		wd[255];

	*hashtable = ft_create_hashtable(250);
	if (!*hashtable)
		stop_when_calloc_fail();
	getcwd(wd, 255);
	ft_add_element(hashtable, "PWD", wd);
	ft_add_element(hashtable, "SHLVL", "1");
	ft_add_element(hashtable, "_", "env");
}

void	ft_create_hidden(t_hashtable **hashtable)
{
	*hashtable = ft_create_hashtable(10);
	if (!hashtable)
		stop_when_calloc_fail();
	ft_add_element(hashtable, "PATH",
		"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	ft_add_element(hashtable, "?", "0");
}

char	*htab_element_to_str(t_element *element)
{
	char	*tmp;
	char	*str;

	str = ft_strjoin("", element->key);
	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strjoin(str, "=");
	free(tmp);
	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strjoin(str, element->value);
	free(tmp);
	if (!str)
		return (NULL);
	return (str);
}
